#pragma once
#pragma comment(lib, "ws2_32.lib")

#include <WS2tcpip.h>
#include <WinSock2.h>
#include <assert.h>
#include <iostream>

// ���� :
class Server
{
public:
	// constrcuter destructer
	Server();
	~Server();

	/// <summary>
	/// Server�� Open�ϱ� ���� �ʱ� ����
	/// </summary>
	void ServerOpen();

	SOCKET GetSocket() const
	{
		return AcceptSocket;
	}

protected:

private:
	// ������ �� ���� (1��1 ����̴ϱ� 1)
	int BackLog = 1;
	// ��Ʈ��ȣ ����
	int Port = 30000;
	// ��ſ� Ȱ���� ����
	SOCKET AcceptSocket = SOCKET();
};

