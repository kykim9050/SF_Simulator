
#include "Server.h"


Server::Server()
{
}

Server::~Server()
{
	// ������ ��ȯ
	while (0 != RecvThreads.size())
	{
		for (size_t i = 0; i < RecvThreads.size(); i++)
		{
			if (true == RecvThreads[i].joinable())
			{
				RecvThreads[i].join();
			}
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
}

void Server::ServerRecvThread(SOCKET _Socket)
{
	while (true)
	{
		int a = 0;
	}
}

