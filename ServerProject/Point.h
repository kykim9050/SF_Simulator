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

	// �⺻ �Ҹ���
	~Point()
	{

	}

	/// <summary>
	/// Point ���
	/// </summary>
	int X = -1;
	int Y = -1;
};

