#include "WayPointAlgo.h"
#include <queue>
#include <iostream>

void WayPointAlgo::FindPathWithBFS(std::vector<std::vector<int>>& _GridMap, const Point& _StartPos, const Point& _DestPos, std::stack<Point>& _ResPath)
{
	int Size = static_cast<int>(_GridMap.size());
	std::queue<Point> Q = std::queue<Point>();
	std::vector<std::vector<bool>> Visited = std::vector<std::vector<bool>>(Size, std::vector<bool>(Size, false));
	// �� �׸��� ��Ҹ��� � ��ġ ��ġ���� �Ļ��Ǿ������� ���� ����
	// _ResPath�� ��θ� �־ ������ �� �ʿ�
	std::vector<std::vector<Point>> ParentPos = std::vector<std::vector<Point>>(Size, std::vector<Point>(Size, Point(-1, -1)));

	Point CurPos = Point(_StartPos);
	Point EndPos = _DestPos;

	Q.push(CurPos);
	Visited[CurPos.X][CurPos.Y] = true;
	
	// ���� ��ġ�� �̸� Stack�� �־���´�.
	_ResPath.push(EndPos);
	// ������ �ձ��� �� �� �ֵ��� X�� +1
	EndPos.X += 1;


	// Q�� ���� ��ǥ���� Pop�ϸ鼭 ��ǥ �̵�
	// _DestPos�� ������ �� ��θ� ã�� ��
	while (!Q.empty())
	{
		CurPos = Q.front();
		Q.pop();

		if (CurPos == EndPos)
		{
			// ��� ��� ���� ����
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
			
			// ��ȿ�� ��ǥ ��������, �湮���� �ʾҰų� �� �� �ִ� ������ Ȯ��
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
