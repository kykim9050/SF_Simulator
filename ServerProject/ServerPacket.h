#pragma once
#include "ServerProtocol.h"

// ���� : Server �� ��Ŷ ����

enum class EPacketType
{
	None,
	NValuePacket = 100,		// N�� ���� ��Ŷ
	MoverCoursePacket,	// �̵�ü ��ΰ��� ��Ŷ
};

class RecvNValuePacket : public ServerProtocol
{
public:
	RecvNValuePacket()
	{
		SetType(EPacketType::NValuePacket);
	}

	void Serialize(ServerSerializer& _Ser) override
	{
		ServerProtocol::Serialize(_Ser);
	}

	void DeSerialize(ServerSerializer& _Ser) override
	{
		ServerProtocol::DeSerialize(_Ser);
	}
};

class SendNValuePacket : public ServerProtocol
{
public:
	SendNValuePacket()
	{
		SetType(EPacketType::NValuePacket);
	}

	void Serialize(ServerSerializer& _Ser) override
	{
		ServerProtocol::Serialize(_Ser);
		_Ser << NValue;
	}

	void DeSerialize(ServerSerializer& _Ser) override
	{
		ServerProtocol::DeSerialize(_Ser);
		_Ser >> NValue;
	}

public:
	// NValue ��
	int NValue = -1;
};
