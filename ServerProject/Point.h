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

	/// <summary>
	/// Point 요소
	/// </summary>
	int X = -1;
	int Y = -1;
};

