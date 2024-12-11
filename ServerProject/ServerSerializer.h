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

	inline char* DataCharPtrToReadOffset()
	{
		return &Data[ReadOffset];
	}

	inline int RemainSize()
	{
		return static_cast<int>(Data.size()) - WriteOffset;
	}

	inline void AddWriteOffset(int _Offset)
	{
		WriteOffset += _Offset;
	}

	inline int GetWriteOffset() const
	{
		return WriteOffset;
	}

	inline void AddReadOffset(int _Offset)
	{
		ReadOffset += _Offset;
	}

	inline int GetReadOffset() const
	{
		return ReadOffset;
	}

	void Write(const void* _Data, size_t _Size);

	void operator<<(const int& _Data);
	void operator<<(const unsigned int& _Data);

	void Read(void* _Data, size_t _Size);

	void operator>>(int& _Data);
	void operator>>(unsigned int& _Data);

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
