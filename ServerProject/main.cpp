#include <iostream>
#include "WayPointAlgo.h"
#include "Point.h"

#include <vector>
#include "Display.h"


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

	// ȭ�鿡 �׸��� ���� ��Ȳ�� ������
	Display Dis = Display();
	Dis.Print2DMap<int>(GridMap);
	std::cout << std::endl;

	GridMap[N - 1][N - 1] = 10;

	WayPointAlgo NewAlgo = WayPointAlgo(23, Point(4,4), Point(1,1));
	NewAlgo.FindPath();

	Dis.Print2DMap<int>(GridMap);
	
	return 0;
}