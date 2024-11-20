#include <iostream>
#include "WayPointAlgo.h"
#include "Point.h"

#include <vector>
#include "Display.h"
#include <algorithm>
#include <random>


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


	// 화면에 그리드 맵의 상황을 보여줌
	Display Dis = Display();
	Dis.Print2DMap<int>(GridMap);

	WayPointAlgo NewAlgo = WayPointAlgo(23, Point(4,4), Point(1,1));
	NewAlgo.FindPath();
	
	return 0;
}