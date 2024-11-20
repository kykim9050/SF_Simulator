#pragma once

// 설명 : 2차원 벡터값인 Point를 정의하는 구조체
struct Point
{
	// 기본 생성자
	Point()
	{

	}

	Point(int _X, int _Y)
		:X(_X)
		,Y(_Y)
	{

	}

	// 기본 소멸자
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
	/// Point 요소
	/// </summary>
	int X = -1;
	int Y = -1;
};

