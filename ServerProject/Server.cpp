
#include "Server.h"


Server::Server()
{
}

Server::~Server()
{
	// 스레드 반환
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
}

void Server::ServerRecvThread(SOCKET _Socket)
{
	while (true)
	{
		int a = 0;
	}
}

