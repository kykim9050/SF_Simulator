#pragma once
#include "ServerProtocol.h"

// ���� : Server �� ��Ŷ ����

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

	void Serialize(ServerSerializer& _Ser) override
	{
		ServerProtocol::Serialize(_Ser);
	}

	void DeSerialize(ServerSerializer& _Ser) override
	{
		ServerProtocol::DeSerialize(_Ser);
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
