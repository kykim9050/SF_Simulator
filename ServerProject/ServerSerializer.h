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

class SerializeObject
{
public:
	virtual void Serialize(ServerSerializer& _Ser) = 0;
	virtual void DeSerialize(ServerSerializer& _Ser) = 0;
};
