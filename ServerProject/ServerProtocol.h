#pragma once
#include <memory>
#include "ServerSerializer.h"


// 설명 : Server 측 프로토콜 클래스
class ServerProtocol : public std::enable_shared_from_this<ServerProtocol>, public SerializeObject
{
public:

	ServerProtocol()
		:Type(0)
		,Size(0)
	{

	}

	ServerProtocol(unsigned int _Type, unsigned int _Size)
		:Type(_Type)
		, Size(_Size)
	{

	}

	// delete Function
	ServerProtocol(const ServerProtocol& _Other) = delete;
	ServerProtocol(ServerProtocol&& _Other) noexcept = delete;
	ServerProtocol& operator=(const ServerProtocol& _Other) = delete;
	ServerProtocol& operator=(ServerProtocol&& _Other) noexcept = delete;

	void Serialize(ServerSerializer& _Ser) override
	{
		_Ser << Type;
		_Ser << Size;
	}

	void DeSerialize(ServerSerializer& _Ser) override
	{
		_Ser >> Type;
		_Ser >> Size;
	}

	unsigned int GetPacketType() const
	{
		return Type;
	}

protected:
	unsigned int Type = 0;
	unsigned int Size = 0;

	template<typename PType>
	void SetType(PType _Type)
	{
		Type = static_cast<unsigned int>(_Type);
	}

private:

};

