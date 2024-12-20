#pragma comment(lib, "ws2_32.lib")

#include <WS2tcpip.h>
#include <WinSock2.h>
#include <assert.h>
#include <iostream>
#include <vector>
#include <thread>

#include "WayPointAlgo.h"
#include "Point.h"
#include "Server.h"
#include "GlobalValue.h"

// For Test Include
#include "Display.h"
#include <algorithm>
#include <random>
#include <map>


int main(void)
{
	int N = -1;

	while (true)
	{
		std::cout << "Input N (5 <= N <= 10) : ";
		std::cin >> N;
		GlobalValue::GetInst().SetNValue(N);

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

	// 그리드 맵 생성
	std::vector<std::vector<int>> GridMap = std::vector<std::vector<int>>(N, std::vector<int>(N));
	
	//// 임시 랜덤 생성기 (랜덤 시드를 메모리 주소로 활용)
	//// 그리드 내 도착지 Random
	//for (int i = 0; i < N; ++i)
	//{
	//	GridMap[0][i] = i + 1;
	//}
	//int RandA = 0;
	//uint64_t AddressA = reinterpret_cast<uint64_t>(&RandA);
	//std::shuffle(GridMap[0].begin(), GridMap[0].end(), std::default_random_engine(std::mt19937(static_cast<unsigned int>(AddressA))));
	//// 그리드 내 로봇 random생성
	//for (int i = 0; i < N; ++i)
	//{
	//	GridMap[N - 1][i] = i + 1;
	//}
	//int RandB = 0;
	//uint64_t AddressB = reinterpret_cast<uint64_t>(&RandB);
	//std::shuffle(GridMap[N - 1].begin(), GridMap[N - 1].end(), std::default_random_engine(std::mt19937(static_cast<unsigned int>(AddressB))));

	//// 목적지와 이동체 1대1 매핑
	//// pair의 first는 출발지 위치, second는 도착지 위치
	//std::map<int, std::pair<Point, Point>> MatchingInfo = std::map<int, std::pair<Point, Point>>();
	//for (int i = 0; i < N; ++i)
	//{
	//	MatchingInfo[i + 1] = std::make_pair<Point, Point>(Point(), Point());
	//}
	//for (int i = 0; i < N; ++i)
	//{
	//	MatchingInfo[GridMap[N - 1][i]].first = Point(N - 1, i);
	//	MatchingInfo[GridMap[0][i]].second = Point(0, i);
	//}

	//// 화면에 그리드 맵의 상황을 보여줌
	//Display Dis = Display();
	//std::cout << "------Init-------" << std::endl;
	//Dis.Print2DMap<int>(GridMap);

	//std::stack<Point> PathStack = std::stack<Point>();
	//WayPointAlgo NewAlgo = WayPointAlgo();

	//for (int i = 1; i <= N; ++i)
	//{
	//	NewAlgo.FindPathWithBFS(GridMap, MatchingInfo[i].first, MatchingInfo[i].second, PathStack);

	//	// 경로 출력
	//	std::cout << std::endl;
	//	std::cout << "------[ID :" << i << "] ResultPath------- " << std::endl;
	//	while (!PathStack.empty())
	//	{
	//		Point Pos = PathStack.top();
	//		std::cout << "{" << Pos.X << "," << Pos.Y << "}" << " ";
	//		PathStack.pop();
	//	}
	//}


	// 서버 열기
	std::shared_ptr<Server> MainServer = std::make_shared<Server>();
	MainServer->ServerOpen();

	SOCKET ServerSocket = MainServer->GetSocket();

	// 수신 받을 클라이언트의 주소 길이사이즈
	int AddressLen = sizeof(SOCKADDR_IN);

	while (true)
	{
		// Client 접속시 클라이언트의 소켓 정보를 받아오기 위함
		SOCKADDR_IN ClientAddress = SOCKADDR_IN();
		memset(&ClientAddress, 0, sizeof(SOCKADDR_IN));
		// 접속자가 있다면 작동 (클라 접속 존재시)
		SOCKET ClientSocket = accept(ServerSocket, (sockaddr*)&ClientAddress, &AddressLen);
	
		// accept 수행 이후 반환받은 ClientSocket으로 별도의 스레드를 생성해 통신하기 위한 사전 작업
		MainServer->AddSocket(ClientSocket);
		MainServer->AddRecvThread(ClientSocket);

		std::cout << "Client Accept!!" << std::endl;
	}

	return 0;
}