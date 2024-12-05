#pragma once
#include "ServerProtocol.h"

// ���� : Server �� ��Ŷ ����

enum class EPacketType
{
	RecvPacket,
	SendPacket,
};

enum class ERequestType
{
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
	// ��û ���� Ÿ��
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
