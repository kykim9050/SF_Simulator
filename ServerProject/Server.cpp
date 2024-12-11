
#include "Server.h"
#include "ServerSerializer.h"
#include "ServerProtocol.h"
#include "GlobalValue.h"


Server::Server()
{
}

Server::~Server()
{
	// 스레드 반환
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

	//// 소켓 정보 초기화
	// 윈도우로부터 소켓을 사용하기 위해 활용하는 구조체 WSData
	WSAData WsaData = WSAData();
	// 윈도우의 소켓을 초기화 하는 함수
	int Error = WSAStartup(MAKEWORD(2, 2), &WsaData);
	if (SOCKET_ERROR == Error)
	{
		// 반환값이 에러에 해당되면 치명적인 오류 발생 (소켓 초기화 오류)
		// 인자가 false에 해당하면 assert 활성화
		assert(false);
	}

	//// 전송 주소, 포트 지정
	SOCKADDR_IN Address = {};
	Address.sin_family = AF_INET;
	Address.sin_port = htons(Port);

	// 네트워크 주소를 인자로 받아 이진수로 출력
	// 서버라서 임의 주소 지정
	if (SOCKET_ERROR == inet_pton(AF_INET, "0.0.0.0", &Address.sin_addr))
	{
		assert(false);
	}

	//// 통신의 매개체인 소켓 생성
	// TCP 사용 - SOCK_STREAM
	AcceptSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == AcceptSocket)
	{
		assert(false);
	}

	//// 소켓과 주소 바인딩
	// AcceptSocket주소로 수신,송신 하면 Address 주소와 연결되어 행해짐
	if (INVALID_SOCKET == bind(AcceptSocket, (const sockaddr*)&Address, sizeof(SOCKADDR_IN)))
	{
		assert(false);
	}

	//// 실제 서버를 열고 클라이언트의 연결을 가능하도록 준비
	if (SOCKET_ERROR == listen(AcceptSocket, BackLog))
	{
		assert(false);
	}

	std::cout << "Listen....." << std::endl;

	// 패킷 별 실행 코드 초기화
	ServerPacketInit(Interpret);
}

void Server::ServerRecvThread(SOCKET _Socket)
{
	// 데이터를 수신 받을 Serializer
	ServerSerializer Ser = ServerSerializer();
	Ser.BufferResize(1024);

	while (SOCKET_ERROR != _Socket)
	{
		// 현재 시리얼라이즈의 WriteOffset부터 데이터를 남은 사이즈 만큼 데이터 수신
		int RecvSize = recv(_Socket, Ser.DataCharPtrToWriteOffset(), Ser.RemainSize(), 0);
		
		if (SOCKET_ERROR == RecvSize)
		{
			return;
		}

		if (-1 == RecvSize)
		{
			return;
		}
		
		// 시리얼라이즈에서 쓴 길이만큼을 WriteOffset 값에 추가
		Ser.AddWriteOffset(RecvSize);

		// 읽어들인 데이터의 길이가 헤더의 사이즈보다 작다면 문제가 있는 것이기에 다시 받음
		if (HeaderSize > Ser.GetWriteOffset())
		{
			continue;
		}

		// 역직렬화
		ServerProtocol Protocol = ServerProtocol();
		// 패킷의 헤더 정보 가져오기 (뒤에 읽을 데이터의 수와 종류를 파악하기 위함)
		Protocol.DeSerialize(Ser);

		// 헤더 정보를 읽었으니 다시 앞으로 이동
		Ser.AddReadOffset(-8);

		if (Ser.GetReadOffset() > 1024)
		{
			return;
		}

		// 프로토콜을 해석
		std::shared_ptr<ServerProtocol> NewProtocol = Interpret.ConvertProtocol(Protocol.GetPacketType(), Ser);
		// 해당 프로토콜에 맞는 액션 실행
		Interpret.ProcessPacket(NewProtocol);

		// 남은 패킷 정보 읽기
	}
}

void Server::ServerPacketInit(Interpreter& _Interpret)
{
	int N = GlobalValue::GetInst().GetNValue();

	_Interpret.AddHandler<RecvPacket>([this, N](std::shared_ptr<RecvPacket> _Packet)
		{
			int Type = _Packet.get()->RequestType;

			switch (Type)
			{
			case static_cast<int>(ERequestType::GetNValue):
			{
				// 패킷 구성 및 전달 방법
				// 1. 패킷의 Payload 만 데이터를 구성한다 (Const Char*형식으로)
				// 2. 헤더를 만들어서 size에 Payload의 사이즈를 전달한다.
				// 3. 헤더를 만든 후에 size까지 갱신이되면 이후로 Payload데이터를 그대로 붙인다. (패킷완성)

				// Test 패킷 (어떻게든 패킷을 구성하면 클라에서 받는지에 대한 테스트))
				// 전달할 패킷을 구성 (N값이 포함된)
				SendNValuePacket SendPacket = SendNValuePacket(1, N);
				ServerSerializer Ser = ServerSerializer();
				SendPacket.Serialize(Ser);

				// BroadCast
				for (auto ClientSocket : ClientSockets)
				{
					// 패킷을 만들었기 때문에 읽기 오프셋은 초기 0
					// 쓴 오프셋 크기만큼 전달
					send(ClientSocket, Ser.DataCharPtrToReadOffset(), Ser.GetWriteOffset(), 0);
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
}

