#pragma once
#include "ServerProtocol.h"

// 설명 : Server 측 패킷 모음

enum class EPacketType
{
	RecvPacket,
	SendPacket,
};

class RecvPacket : public ServerProtocol
{
public:
	RecvPacket()
	{
		SetType(EPacketType::RecvPacket);
	}

protected:

private:

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
