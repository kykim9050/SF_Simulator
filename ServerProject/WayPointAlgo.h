#pragma once
#include "Point.h"
#include <vector>
#include <stack>

// 설명 : WayPoint 알고리즘을 담당하는 클래스
class WayPointAlgo
{
public:
	/// <summary>
	/// 기본 생성자
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
	/// 기본 소멸자
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
	/// Input 정보를 토대로 경로를 찾는 알고리즘
	/// </summary>
	void FindPathWithBFS(std::vector<std::vector<int>>& _GridMap, const Point& _StartPos, const Point& _DestPos, std::stack<Point>& _ResPath);

	/// <summary>
	/// GridMap 정보를 받아들여서 ResPath에 경로를 입력하는 함수
	/// </summary>
	/// <param name="_GridMap"></param>
	/// <param name="_ResPath"></param>
	void FindPathWithBFS(std::vector<std::vector<int>>& _GridMap, std::stack<Point>& _ResPath);

protected:

private:
	/// <summary>
	/// 이동체 ID
	/// </summary>
	int RobotID = -1;

	// 출발지 좌표
	Point StartPos = Point();

	// 목적지 좌표
	Point DestPos = Point();

	// 상, 좌, 우 이동 (하 이동은 생략)
	std::vector<int> Dx = std::vector<int>{ -1, 0, 0 };
	std::vector<int> Dy = std::vector<int>{ 0, -1, 1 };
};

