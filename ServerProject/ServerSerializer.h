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

class SerializeObject
{
public:
	virtual void Serialize(ServerSerializer& _Ser) = 0;
	virtual void DeSerialize(ServerSerializer& _Ser) = 0;
};
