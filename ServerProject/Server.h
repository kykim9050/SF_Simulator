#pragma once
#pragma comment(lib, "ws2_32.lib")

#include <WS2tcpip.h>
#include <WinSock2.h>
#include <assert.h>
#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include "Interpreter.h"
#include "ServerPacket.h"
#include "Point.h"

// 설명 :
class Server
{
public:
	// constrcuter destructer
	Server();
	~Server();

	/// <summary>
	/// Server를 Open하기 위한 초기 설정
	/// </summary>
	void ServerOpen();

	SOCKET GetSocket() const
	{
		return AcceptSocket;
	}

	/// <summary>
	/// 수신용
	/// </summary>
	/// <param name="_Socket"></param>
	void AddSocket(const SOCKET& _Socket)
	{
		ClientSockets.push_back(_Socket);
	}

	void AddRecvThread(const SOCKET& _Socket)
	{
		RecvThreads.push_back(std::thread(std::bind(&Server::ServerRecvThread, this, _Socket)));
	}

	/// <summary>
	/// Client가 보내는 데이터를 처리하는 Recv함수 (스레드를 활용하여 메인 스레드와 병행해 실행)
	/// </summary>
	/// <param name="_Socket"></param>
	void ServerRecvThread(SOCKET _Socket);

	/// <summary>
	/// 서버측 특정 패킷 관련 액션에 대한 초기화 함수
	/// </summary>
	/// <param name="_Interpret"></param>
	void ServerPacketInit(Interpreter& _Interpret);

protected:

private:
	// 접속자 수 지정 (1대1 통신이니까 1)
	int BackLog = 1;
	// 포트번호 지정
	int Port = 30000;
	// 통신에 활용할 소켓
	SOCKET AcceptSocket = SOCKET();

	// 연결된 소켓들을 보관
	std::vector<SOCKET> ClientSockets = std::vector<SOCKET>();
	// 특정 소켓별로 Thread를 할당하여 보관
	std::vector<std::thread> RecvThreads = std::vector<std::thread>();

	// 헤더의 사이즈
	int HeaderSize = 8;

	// 서버 전용 해석자
	Interpreter Interpret = Interpreter();

private:
	int Send(SOCKET _ClientSocket, std::shared_ptr<ServerProtocol> _Protocol);

	int Send(SOCKET _ClientSocket, ServerSerializer& _Ser);
};

