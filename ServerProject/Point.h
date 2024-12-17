#pragma once

// ���� : 2���� ���Ͱ��� Point�� �����ϴ� ����ü
struct Point
{
	// �⺻ ������
	Point()
	{

	}

	Point(int _X, int _Y)
		:X(_X)
		,Y(_Y)
	{

	}

	Point(double _X, double _Y)
		:X(static_cast<int>(_X))
		, Y(static_cast<int>(_Y))
	{

	}

	// �⺻ �Ҹ���
	~Point()
	{

	}

	bool operator==(Point& _OtherPos)
	{
		return (X == _OtherPos.X && Y == _OtherPos.Y);
	}

	bool operator==(const Point& _OtherPos)
	{
		return (X == _OtherPos.X && Y == _OtherPos.Y);
	}

	bool operator!=(Point& _OtherPos)
	{
		return !(X == _OtherPos.X && Y == _OtherPos.Y);
	}

	bool operator!=(const Point& _OtherPos)
	{
		return !(X == _OtherPos.X && Y == _OtherPos.Y);
	}

	Point& operator=(const Point& _OtherPos)
	{
		X = _OtherPos.X;
		Y = _OtherPos.Y;
		return *this;
	}

	/// <summary>
	/// Point ���
	/// </summary>
	int X = -1;
	int Y = -1;
};

