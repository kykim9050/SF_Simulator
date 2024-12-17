#pragma once
#include "Point.h"
#include <vector>
#include <stack>

// ���� : WayPoint �˰����� ����ϴ� Ŭ����
class WayPointAlgo
{
public:
	/// <summary>
	/// �⺻ ������
	/// </summary>
	WayPointAlgo()
	{

	}

	WayPointAlgo(int _RobotID, Point _StartPos, Point _DestPos)
		: RobotID(_RobotID)
		, StartPos(_StartPos)
		, DestPos(_DestPos)
	{

	}

	/// <summary>
	/// �⺻ �Ҹ���
	/// </summary>
	~WayPointAlgo()
	{

	}

	// delete Function
	//WayPointAlgo(const WayPointAlgo& _Other) = delete;
	//WayPointAlgo(WayPointAlgo&& _Other) noexcept = delete;
	//WayPointAlgo& operator=(const WayPointAlgo& _Other) = delete;
	//WayPointAlgo& operator=(WayPointAlgo&& _Other) noexcept = delete;

	int GetRobotID() const
	{
		return RobotID;
	}

	Point GetStartPos() const
	{
		return StartPos;
	}

	Point GetDestPos() const
	{
		return DestPos;
	}

	/// <summary>
	/// Input ������ ���� ��θ� ã�� �˰���
	/// </summary>
	void FindPathWithBFS(std::vector<std::vector<int>>& _GridMap, const Point& _StartPos, const Point& _DestPos, std::stack<Point>& _ResPath);

	/// <summary>
	/// GridMap ������ �޾Ƶ鿩�� ResPath�� ��θ� �Է��ϴ� �Լ�
	/// </summary>
	/// <param name="_GridMap"></param>
	/// <param name="_ResPath"></param>
	void FindPathWithBFS(std::vector<std::vector<int>>& _GridMap, std::stack<Point>& _ResPath);

protected:

private:
	/// <summary>
	/// �̵�ü ID
	/// </summary>
	int RobotID = -1;

	// ����� ��ǥ
	Point StartPos = Point();

	// ������ ��ǥ
	Point DestPos = Point();

	// ��, ��, �� �̵� (�� �̵��� ����)
	std::vector<int> Dx = std::vector<int>{ -1, 0, 0 };
	std::vector<int> Dy = std::vector<int>{ 0, -1, 1 };
};

