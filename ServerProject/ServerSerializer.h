#pragma once
#include <vector>

// ���� :
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
