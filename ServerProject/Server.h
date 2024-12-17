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

	/// <summary>
	/// ���ſ�
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
	/// Client�� ������ �����͸� ó���ϴ� Recv�Լ� (�����带 Ȱ���Ͽ� ���� ������� ������ ����)
	/// </summary>
	/// <param name="_Socket"></param>
	void ServerRecvThread(SOCKET _Socket);

	/// <summary>
	/// ������ Ư�� ��Ŷ ���� �׼ǿ� ���� �ʱ�ȭ �Լ�
	/// </summary>
	/// <param name="_Interpret"></param>
	void ServerPacketInit(Interpreter& _Interpret);

protected:

private:
	// ������ �� ���� (1��1 ����̴ϱ� 1)
	int BackLog = 1;
	// ��Ʈ��ȣ ����
	int Port = 30000;
	// ��ſ� Ȱ���� ����
	SOCKET AcceptSocket = SOCKET();

	// ����� ���ϵ��� ����
	std::vector<SOCKET> ClientSockets = std::vector<SOCKET>();
	// Ư�� ���Ϻ��� Thread�� �Ҵ��Ͽ� ����
	std::vector<std::thread> RecvThreads = std::vector<std::thread>();

	// ����� ������
	int HeaderSize = 8;

	// ���� ���� �ؼ���
	Interpreter Interpret = Interpreter();

private:
	int Send(SOCKET _ClientSocket, std::shared_ptr<ServerProtocol> _Protocol);

	int Send(SOCKET _ClientSocket, ServerSerializer& _Ser);
};

