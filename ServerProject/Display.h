#pragma once
#include <vector>
#include <iostream>

// ���� : 2���� ��� �����͸� �޾� ȭ�鿡 ������ִ� Ŭ����
class Display
{
public:
	// constrcuter destructer
	Display();
	~Display();

	/// <summary>
	/// 2D ���͸� ȭ�鿡 ǥ���� �� �ִ� �Լ�
	/// </summary>
	/// <typeparam name="Type"></typeparam>
	/// <param name="_2DMap"></param>
	template <typename Type>
	void Print2DMap(std::vector<std::vector<Type>>& _2DMap)
	{
		size_t ColSize = _2DMap.size();
		size_t RowSize = _2DMap[0].size();

		for (size_t i = 0; i < ColSize; ++i)
		{
			for (size_t j = 0; j < RowSize; ++j)
			{
				std::cout << _2DMap[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

protected:

private:

};

