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

	// �׸��� �� ����
	std::vector<std::vector<int>> GridMap = std::vector<std::vector<int>>(N, std::vector<int>(N));
	// �׸��� �� ������ Random
	for (int i = 0; i < N; ++i)
	{
		GridMap[0][i] = i + 1;
	}
	std::shuffle(GridMap[0].begin(), GridMap[0].end(), std::default_random_engine());
	// �׸��� �� �κ� random����
	for (int i = 0; i < N; ++i)
	{
		GridMap[N-1][i] = i + 1;
	}
	std::shuffle(GridMap[N-1].begin(), GridMap[N-1].end(), std::default_random_engine());

	// ȭ�鿡 �׸��� ���� ��Ȳ�� ������
	Display Dis = Display();
	Dis.Print2DMap<int>(GridMap);

	WayPointAlgo NewAlgo = WayPointAlgo(23, Point(4,4), Point(1,1));
	NewAlgo.FindPath();
	
	return 0;
}