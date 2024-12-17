#include "WayPointAlgo.h"
#include <queue>
#include <iostream>

void WayPointAlgo::FindPathWithBFS(std::vector<std::vector<int>>& _GridMap, const Point& _StartPos, const Point& _DestPos, std::stack<Point>& _ResPath)
{
	int Size = static_cast<int>(_GridMap.size());
	std::queue<Point> Q = std::queue<Point>();
	std::vector<std::vector<bool>> Visited = std::vector<std::vector<bool>>(Size, std::vector<bool>(Size, false));
	// 각 그리드 요소마다 어떤 위치 위치에서 파생되었는지에 대한 정보
	// _ResPath에 경로를 넣어서 전달할 때 필요
	std::vector<std::vector<Point>> ParentPos = std::vector<std::vector<Point>>(Size, std::vector<Point>(Size, Point(-1, -1)));

	Point CurPos = Point(_StartPos);
	Point EndPos = _DestPos;

	Q.push(CurPos);
	Visited[CurPos.X][CurPos.Y] = true;
	
	// 최종 위치는 미리 Stack에 넣어놓는다.
	_ResPath.push(EndPos);
	// 목적지 앞까지 올 수 있도록 X값 +1
	EndPos.X += 1;


	// Q에 넣은 좌표들을 Pop하면서 좌표 이동
	// _DestPos에 같아질 때 경로를 찾은 것
	while (!Q.empty())
	{
		CurPos = Q.front();
		Q.pop();

		if (CurPos == EndPos)
		{
			// 경로 출력 내용 구현
			while (true)
			{
				if (Point(-1, -1) == CurPos)
				{
					//std::cout << "Find Path" << std::endl;
					return;
				}

				_ResPath.push(CurPos);
				CurPos = ParentPos[CurPos.X][CurPos.Y];
			}
		}

		for (size_t i = 0; i < Dx.size(); ++i)
		{
			Point NextPos = Point(CurPos.X + Dx[i], CurPos.Y + Dy[i]);
			
			// 유효한 좌표 정보인지, 방문하지 않았거나 갈 수 있는 곳인지 확인
			if (0 <= NextPos.X && Size > NextPos.X && 0 <= NextPos.Y && Size > NextPos.Y && /*0 == _GridMap[NextPos.X][NextPos.Y] &&*/ false == Visited[NextPos.X][NextPos.Y])
			{
				Q.push(NextPos);
				Visited[NextPos.X][NextPos.Y] = true;
				ParentPos[NextPos.X][NextPos.Y] = CurPos;
			}
		}
	}

	std::cout << "Not Found Path" << std::endl;
	return;
}

void WayPointAlgo::FindPathWithBFS(std::vector<std::vector<int>>& _GridMap, std::stack<Point>& _ResPath)
{
	FindPathWithBFS(_GridMap, StartPos, DestPos, _ResPath);
}
