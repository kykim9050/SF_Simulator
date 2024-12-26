#pragma once
#include <vector>
#include <string>

// ���� :
class ServerSerializer
{
public:
	// constrcuter destructer
	ServerSerializer();
	~ServerSerializer();

	void Paste(int _Offset, const void* _Data, size_t _Size);

	inline char* DataPtr()
	{
		return &Data[0];
	}

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

	inline int WriteSize() const
	{
		return GetWriteOffset();
	}

	inline void AddReadOffset(int _Offset)
	{
		ReadOffset += _Offset;
	}

	inline int GetReadOffset() const
	{
		return ReadOffset;
	}

	inline int BufferSize() const
	{
		return static_cast<int>(Data.size());
	}

	inline void Reset()
	{
		WriteOffset = 0;
		ReadOffset = 0;
	}

	void DataToReadOffsetPush();

	void Write(const void* _Data, size_t _Size);
	void operator<<(const int& _Data);
	void operator<<(const unsigned int& _Data);
	void operator<<(const double& _Data);
	void operator<<(const std::vector<int>& _Data);

	void Read(void* _Data, size_t _Size);
	void operator>>(int& _Data);
	void operator>>(unsigned int& _Data);
	void operator>>(double& _Data);
	void operator>>(char& _Data);
	void operator>>(std::string& _Data);


protected:

private:
	/// <summary>
	/// �󸶳� �����
	/// </summary>
	int WriteOffset = 0;

	/// <summary>
	/// �󸶳� �о�����
	/// </summary>
	int ReadOffset = 0;

	/// <summary>
	/// Serialize ��� ������ ����
	/// </summary>
	std::vector<char> Data = std::vector<char>();
};

/// <summary>
/// ����ȭ�� �ʿ��� ������Ʈ���� �� ��ӹ޾ƾ� �ϴ� �������̽� Ŭ����
/// </summary>
class SerializeObject
{
public:
	virtual void Serialize(ServerSerializer& _Ser) = 0;
	virtual void DeSerialize(ServerSerializer& _Ser) = 0;
};
