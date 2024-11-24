#pragma comment(lib, "ws2_32.lib")
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <iostream>
#include "WayPointAlgo.h"
#include "Point.h"
#include <vector>
#include "Server.h"
#include <assert.h>

// For Test Include
#include "Display.h"
#include <algorithm>
#include <random>
#include <map>



int main(void)
{
	int N = -1;;

	while (true)
	{
		std::cout << "Input N (5 <= N <= 10) : ";
		std::cin >> N;

		if (5 <= N && 10 >= N)
		{
			break;
		}

		if (5 > N || 10 < N)
		{
			std::cout << "[Error] InCorrect Range. Please Retry Input" << std::endl;
			continue;
		}
	}

	// �׸��� �� ����
	std::vector<std::vector<int>> GridMap = std::vector<std::vector<int>>(N, std::vector<int>(N));
	

	// ---------------------------------
	// ���� ����
	std::cout << "Server Open" << std::endl;
	Server MainServer = Server();

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
	int Port = 30000;
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
	SOCKET AcceptSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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
	// ������ �� ���� (1��1 ����̴ϱ� 1)
	int BackLog = 1;

	if (SOCKET_ERROR == listen(AcceptSocket, BackLog))
	{
		assert(false);
	}
	
	std::cout << "Listen....." << std::endl;

	// -----------------------------









	// �ӽ� ���� ������ (���� �õ带 �޸� �ּҷ� Ȱ��)
	// �׸��� �� ������ Random
	for (int i = 0; i < N; ++i)
	{
		GridMap[0][i] = i + 1;
	}
	int RandA = 0;
	uint64_t AddressA = reinterpret_cast<uint64_t>(&RandA);
	std::shuffle(GridMap[0].begin(), GridMap[0].end(), std::default_random_engine(std::mt19937(static_cast<unsigned int>(AddressA))));
	// �׸��� �� �κ� random����
	for (int i = 0; i < N; ++i)
	{
		GridMap[N-1][i] = i + 1;
	}
	int RandB = 0;
	uint64_t AddressB = reinterpret_cast<uint64_t>(&RandB);
	std::shuffle(GridMap[N-1].begin(), GridMap[N-1].end(), std::default_random_engine(std::mt19937(static_cast<unsigned int>(AddressB))));

	// �������� �̵�ü 1��1 ����
	// pair�� first�� ����� ��ġ, second�� ������ ��ġ
	std::map<int, std::pair<Point, Point>> MatchingInfo = std::map<int, std::pair<Point, Point>>();
	for (int i = 0; i < N; ++i)
	{
		MatchingInfo[i + 1] = std::make_pair<Point, Point>(Point(), Point());
	}
	for (int i = 0; i < N; ++i)
	{
		MatchingInfo[GridMap[N - 1][i]].first = Point(N-1, i);
		MatchingInfo[GridMap[0][i]].second = Point(0, i);
	}


	// ȭ�鿡 �׸��� ���� ��Ȳ�� ������
	Display Dis = Display();
	std::cout << "------Init-------" << std::endl;
	Dis.Print2DMap<int>(GridMap);

	std::stack<Point> PathStack = std::stack<Point>();
	WayPointAlgo NewAlgo = WayPointAlgo();

	for (int i = 1; i <= N; ++i)
	{
		NewAlgo.FindPathWithBFS(GridMap, MatchingInfo[i].first, MatchingInfo[i].second, PathStack);

		// ��� ���
		std::cout << std::endl;
		std::cout << "------[ID :" << i << "] ResultPath------- " << std::endl;
		while (!PathStack.empty())
		{
			Point Pos = PathStack.top();
			std::cout << "{" << Pos.X << "," << Pos.Y << "}" << " ";
			PathStack.pop();
		}
	}

	return 0;
}