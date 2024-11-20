#pragma once
#include "Point.h"

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
	void FindPath();

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
};

