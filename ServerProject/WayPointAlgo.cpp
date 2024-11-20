#include "WayPointAlgo.h"
#include "queue"

void WayPointAlgo::FindPathWithBFS(std::vector<std::vector<int>>& _GridMap, const Point& _StartPos, const Point& _DestPos)
{
	int Size = static_cast<int>(_GridMap.size());
	std::queue<Point> Q = std::queue<Point>();
	std::vector<std::vector<bool>> Visited = std::vector<std::vector<bool>>(Size, std::vector<bool>(Size, false));

	Point CurPos = Point(_StartPos);
	
	Q.push(CurPos);
	Visited[CurPos.X][CurPos.Y] = true;


	int a = 0;
}
