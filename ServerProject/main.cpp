#include <iostream>
#include "WayPointAlgo.h"
#include "Point.h"


int main(void)
{
	WayPointAlgo* NewAlgo = new WayPointAlgo(23, Point(4,4), Point(1,1));

	std::cout << "Input Info" << std::endl;
	std::cout << "Robot ID : " << NewAlgo->GetRobotID() << std::endl;
	std::cout << "Start : " << NewAlgo->GetStartPos().X << ", " << NewAlgo->GetStartPos().Y << std::endl;
	std::cout << "Dest : " << NewAlgo->GetDestPos().X << ", " << NewAlgo->GetDestPos().Y << std::endl;
	
	// 동적 메모리 반환
	delete NewAlgo;
	NewAlgo = nullptr;

	return 0;
}