#pragma once
#include "ServerProtocol.h"

// 설명 : Server 측 패킷 모음

enum class EPacketType
{
	RecvPacket,
	SendPacket,
};

enum class ERequestType
{
	None,
	GetNValue,
	
};

class RecvPacket : public ServerProtocol
{
public:
	RecvPacket()
	{
		SetType(EPacketType::RecvPacket);
	}

	void Serialize(ServerSerializer& _Ser) override
	{
		ServerProtocol::Serialize(_Ser);
		_Ser << RequestType;
	}

	void DeSerialize(ServerSerializer& _Ser) override
	{
		ServerProtocol::DeSerialize(_Ser);
		_Ser >> RequestType;
	}

public:
	// 요청 받은 타입
	int RequestType = -1;
};

class SendPacket : public ServerProtocol
{
public:
	SendPacket()
	{
		SetType(EPacketType::SendPacket);
	}

protected:

private:

};
