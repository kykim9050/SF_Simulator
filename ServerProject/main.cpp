#include <iostream>
#include "WayPointAlgo.h"
#include "Point.h"
#include <vector>

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

	WayPointAlgo NewAlgo = WayPointAlgo();
	NewAlgo.FindPathWithBFS(GridMap, MatchingInfo[1].first, MatchingInfo[1].second);

	// ��� ���
	std::cout << std::endl;
	std::cout << "------Result-------" << std::endl;
	Dis.Print2DMap<int>(GridMap);

	return 0;
}