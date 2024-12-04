#pragma once
#include <vector>

// 설명 :
class ServerSerializer
{
public:
	// constrcuter destructer
	ServerSerializer();
	~ServerSerializer();

	// delete Function
	ServerSerializer(const ServerSerializer& _Other) = delete;
	ServerSerializer(ServerSerializer&& _Other) noexcept = delete;
	ServerSerializer& operator=(const ServerSerializer& _Other) = delete;
	ServerSerializer& operator=(ServerSerializer&& _Other) noexcept = delete;

	inline void BufferResize(unsigned int _Size)
	{
		Data.resize(_Size);
	}

	inline char* DataCharPtrToWriteOffset()
	{
		return &Data[WriteOffset];
	}

	inline int RemainSize()
	{
		return static_cast<int>(Data.size()) - WriteOffset;
	}

protected:

private:
	/// <summary>
	/// 얼마나 썼는지
	/// </summary>
	int WriteOffset = 0;

	/// <summary>
	/// 얼마나 읽었는지
	/// </summary>
	int ReadOffset = 0;

	/// <summary>
	/// Serialize 대상 데이터 모음
	/// </summary>
	std::vector<char> Data = std::vector<char>();
};

/// <summary>
/// 직렬화가 필요한 오브젝트들이 꼭 상속받아야 하는 인터페이스 클래스
/// </summary>
class SerializeObject
{
public:
	virtual void Serialize(ServerSerializer& _Ser) = 0;
	virtual void DeSerialize(ServerSerializer& _Ser) = 0;
};
