#include "WayPointAlgo.h"
#include <queue>
#include <iostream>

void WayPointAlgo::FindPathWithBFS(std::vector<std::vector<int>>& _GridMap, const Point& _StartPos, const Point& _DestPos)
{
	int Size = static_cast<int>(_GridMap.size());
	std::queue<Point> Q = std::queue<Point>();
	std::vector<std::vector<bool>> Visited = std::vector<std::vector<bool>>(Size, std::vector<bool>(Size, false));

	Point CurPos = Point(_StartPos);

	Q.push(CurPos);
	Visited[CurPos.X][CurPos.Y] = true;

	// Q에 넣은 좌표들을 Pop하면서 좌표 이동
	// _DestPos에 같아질 때 경로를 찾은 것
	while (!Q.empty())
	{
		CurPos = Q.front();
		Q.pop();

		if (_DestPos.X == CurPos.X && _DestPos.Y == CurPos.Y)
		{
			// 경로 출력 내용 구현
			std::cout << "Find Path" << std::endl;
			return;
		}

		for (size_t i = 0; i < Dx.size(); ++i)
		{
			Point NextPos = Point(CurPos.X + Dx[i], CurPos.Y + Dy[i]);
			
			// 유효한 좌표 정보인지, 방문하지 않았거나 갈 수 있는 곳인지 확인
			if (0 <= NextPos.X && Size > NextPos.X && 0 <= NextPos.Y && Size > NextPos.Y && /*0 == _GridMap[NextPos.X][NextPos.Y] &&*/ false == Visited[NextPos.X][NextPos.Y])
			{
				Q.push(NextPos);
				Visited[NextPos.X][NextPos.Y] = true;
			}
		}
	}

	std::cout << "Not Found Path" << std::endl;
	return;
}