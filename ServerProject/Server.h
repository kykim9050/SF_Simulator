#pragma once
#pragma comment(lib, "ws2_32.lib")

#include <WS2tcpip.h>
#include <WinSock2.h>
#include <assert.h>
#include <iostream>

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

protected:

private:
	// 접속자 수 지정 (1대1 통신이니까 1)
	int BackLog = 1;
	// 포트번호 지정
	int Port = 30000;
	// 통신에 활용할 소켓
	SOCKET AcceptSocket = SOCKET();
};

