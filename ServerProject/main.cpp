#include <iostream>
#include "WayPointAlgo.h"
#include "Point.h"

#include <vector>

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

	WayPointAlgo NewAlgo = WayPointAlgo(23, Point(4,4), Point(1,1));
	NewAlgo.FindPath();

	std::cout << "Input Info" << std::endl;
	std::cout << "Robot ID : " << NewAlgo.GetRobotID() << std::endl;
	std::cout << "Start : " << NewAlgo.GetStartPos().X << ", " << NewAlgo.GetStartPos().Y << std::endl;
	std::cout << "Dest : " << NewAlgo.GetDestPos().X << ", " << NewAlgo.GetDestPos().Y << std::endl;
	
	return 0;
}