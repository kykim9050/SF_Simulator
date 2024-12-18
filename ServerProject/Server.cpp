
#include "Server.h"
#include "ServerSerializer.h"
#include "ServerProtocol.h"
#include "GlobalValue.h"
#include "WayPointAlgo.h"


Server::Server()
{
}

Server::~Server()
{
	// ������ ��ȯ
	for (size_t i = 0; i < RecvThreads.size(); i++)
	{
		if (true == RecvThreads[i].joinable())
		{
			RecvThreads[i].join();
		}
	}
}

void Server::ServerOpen()
{
	std::cout << "Server Open" << std::endl;

	//// ���� ���� �ʱ�ȭ
	// ������κ��� ������ ����ϱ� ���� Ȱ���ϴ� ����ü WSData
	WSAData WsaData = WSAData();
	// �������� ������ �ʱ�ȭ �ϴ� �Լ�
	int Error = WSAStartup(MAKEWORD(2, 2), &WsaData);
	if (SOCKET_ERROR == Error)
	{
		// ��ȯ���� ������ �ش�Ǹ� ġ������ ���� �߻� (���� �ʱ�ȭ ����)
		// ���ڰ� false�� �ش��ϸ� assert Ȱ��ȭ
		assert(false);
	}

	//// ���� �ּ�, ��Ʈ ����
	SOCKADDR_IN Address = {};
	Address.sin_family = AF_INET;
	Address.sin_port = htons(Port);

	// ��Ʈ��ũ �ּҸ� ���ڷ� �޾� �������� ���
	// ������ ���� �ּ� ����
	if (SOCKET_ERROR == inet_pton(AF_INET, "0.0.0.0", &Address.sin_addr))
	{
		assert(false);
	}

	//// ����� �Ű�ü�� ���� ����
	// TCP ��� - SOCK_STREAM
	AcceptSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == AcceptSocket)
	{
		assert(false);
	}

	//// ���ϰ� �ּ� ���ε�
	// AcceptSocket�ּҷ� ����,�۽� �ϸ� Address �ּҿ� ����Ǿ� ������
	if (INVALID_SOCKET == bind(AcceptSocket, (const sockaddr*)&Address, sizeof(SOCKADDR_IN)))
	{
		assert(false);
	}

	//// ���� ������ ���� Ŭ���̾�Ʈ�� ������ �����ϵ��� �غ�
	if (SOCKET_ERROR == listen(AcceptSocket, BackLog))
	{
		assert(false);
	}

	std::cout << "Listen....." << std::endl;

	// ��Ŷ �� ���� �ڵ� �ʱ�ȭ
	ServerPacketInit(Interpret);
}

void Server::ServerRecvThread(SOCKET _Socket)
{
	// �����͸� ���� ���� Serializer
	ServerSerializer Ser = ServerSerializer();
	Ser.BufferResize(1024);

	while (SOCKET_ERROR != _Socket)
	{
		// ���� �ø���������� WriteOffset���� �����͸� ���� ������ ��ŭ ������ ����
		int RecvSize = recv(_Socket, Ser.DataCharPtrToWriteOffset(), Ser.RemainSize(), 0);
		
		if (SOCKET_ERROR == RecvSize)
		{
			return;
		}

		if (-1 == RecvSize)
		{
			return;
		}
		
		// �ø��������� �� ���̸�ŭ�� WriteOffset ���� �߰�
		Ser.AddWriteOffset(RecvSize);

		// �о���� �������� ���̰� ����� ������� �۴ٸ� ������ �ִ� ���̱⿡ �ٽ� ����
		if (HeaderSize > Ser.GetWriteOffset())
		{
			continue;
		}

		// ������ȭ
		ServerProtocol Protocol = ServerProtocol();
		// ��Ŷ�� ��� ���� �������� (�ڿ� ���� �������� ���� ������ �ľ��ϱ� ����)
		Protocol.DeSerialize(Ser);

		// ��� ������ �о����� �ٽ� ������ �̵�
		Ser.AddReadOffset(-8);

		if (Ser.GetReadOffset() > 1024)
		{
			return;
		}

		// ���������� �ؼ�
		std::shared_ptr<ServerProtocol> NewProtocol = Interpret.ConvertProtocol(Protocol.GetPacketType(), Ser);
		// �ش� �������ݿ� �´� �׼� ����
		Interpret.ProcessPacket(NewProtocol);

		// ���� ��Ŷ ���� �б�
	}
}

void Server::ServerPacketInit(Interpreter& _Interpret)
{
	int N = GlobalValue::GetInst().GetNValue();

	_Interpret.AddHandler<RecvNValuePacket>([this, N](std::shared_ptr<RecvNValuePacket> _Packet)
		{
			int Type = _Packet.get()->GetPacketType();

			switch (Type)
			{
			case static_cast<int>(EPacketType::NValuePacket):
			{
				// SendNValuePacket ��ü ���� (N �����͸� �������)
				std::shared_ptr<SendNValuePacket> SendPacket = std::make_shared<SendNValuePacket>();
				SendPacket->NValue = N;

				// BroadCast
				for (auto ClientSocket : ClientSockets)
				{
					Server::Send(ClientSocket, SendPacket);
				}

				std::cout << "Give N Value" << std::endl;
				break;
			}
			default:
			{
				std::cout << "Invalid Request Type!" << std::endl;
				break;
			}
			}
		});

	_Interpret.AddHandler<RecvMoverCoursePacket>([this, N](std::shared_ptr<RecvMoverCoursePacket> _Packet)
		{
			int MoverID = _Packet->ID;
			Point StartPos{ _Packet->StartXPos, _Packet->StartYPos };
			Point DestPos{ _Packet->DestXPos, _Packet->DestYPos };

			std::vector<std::vector<int>> GridMap = std::vector<std::vector<int>>(N, std::vector<int>(N));
			std::stack<Point> PathStack = std::stack<Point>();

			WayPointAlgo PathAlgo{ MoverID, StartPos , DestPos };
			PathAlgo.FindPathWithBFS(GridMap, PathStack);

			std::shared_ptr<SendMoverCoursePacket> SendPacket = std::make_shared<SendMoverCoursePacket>();
			SendPacket->ID = MoverID;
			SendPacket->PathInfoSize = static_cast<int>(PathStack.size() * 2);

			while (!PathStack.empty())
			{
				Point Pos = PathStack.top();
				SendPacket->AddPathInfo(Pos);
				PathStack.pop();
			}
			
			// BroadCast
			for (auto ClientSocket : ClientSockets)
			{
				Server::Send(ClientSocket, SendPacket);
			}

			std::cout << "Give Path Info" << std::endl;
		});
}

int Server::Send(SOCKET _ClientSocket, std::shared_ptr<ServerProtocol> _Protocol)
{
	// ServerProtocol�� GetSerialize�Լ� ȣ��� ������ ����
	ServerSerializer Ser = _Protocol->GetSerialize();

	// �ø������� Send(Serlialize) �� ����
	return Send(_ClientSocket, Ser);
}

int Server::Send(SOCKET _ClientSocket, ServerSerializer& _Ser)
{
	const char* buf = _Ser.DataPtr();
	int len = _Ser.WriteSize();
	return send(_ClientSocket, buf, len, 0);
}



