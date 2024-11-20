#pragma once
#include <vector>
#include <iostream>

// 설명 : 2차원 행렬 데이터를 받아 화면에 출력해주는 클래스
class Display
{
public:
	// constrcuter destructer
	Display();
	~Display();

	/// <summary>
	/// 2D 벡터를 화면에 표현할 수 있는 함수
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

