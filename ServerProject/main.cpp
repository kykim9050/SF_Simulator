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

	// 그리드 맵 생성
	std::vector<std::vector<int>> GridMap = std::vector<std::vector<int>>(N, std::vector<int>(N));
	

	// ---------------------------------
	// 서버 열기
	std::cout << "Server Open" << std::endl;
	Server MainServer = Server();

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
	int Port = 30000;
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
	SOCKET AcceptSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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
	// 접속자 수 지정 (1대1 통신이니까 1)
	int BackLog = 1;

	if (SOCKET_ERROR == listen(AcceptSocket, BackLog))
	{
		assert(false);
	}
	
	std::cout << "Listen....." << std::endl;

	// -----------------------------









	// 임시 랜덤 생성기 (랜덤 시드를 메모리 주소로 활용)
	// 그리드 내 도착지 Random
	for (int i = 0; i < N; ++i)
	{
		GridMap[0][i] = i + 1;
	}
	int RandA = 0;
	uint64_t AddressA = reinterpret_cast<uint64_t>(&RandA);
	std::shuffle(GridMap[0].begin(), GridMap[0].end(), std::default_random_engine(std::mt19937(static_cast<unsigned int>(AddressA))));
	// 그리드 내 로봇 random생성
	for (int i = 0; i < N; ++i)
	{
		GridMap[N-1][i] = i + 1;
	}
	int RandB = 0;
	uint64_t AddressB = reinterpret_cast<uint64_t>(&RandB);
	std::shuffle(GridMap[N-1].begin(), GridMap[N-1].end(), std::default_random_engine(std::mt19937(static_cast<unsigned int>(AddressB))));

	// 목적지와 이동체 1대1 매핑
	// pair의 first는 출발지 위치, second는 도착지 위치
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


	// 화면에 그리드 맵의 상황을 보여줌
	Display Dis = Display();
	std::cout << "------Init-------" << std::endl;
	Dis.Print2DMap<int>(GridMap);

	std::stack<Point> PathStack = std::stack<Point>();
	WayPointAlgo NewAlgo = WayPointAlgo();

	for (int i = 1; i <= N; ++i)
	{
		NewAlgo.FindPathWithBFS(GridMap, MatchingInfo[i].first, MatchingInfo[i].second, PathStack);

		// 경로 출력
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