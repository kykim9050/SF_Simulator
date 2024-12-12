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

	SendPacket(int _ResType)
		:ResponseType(_ResType)
	{
		SetType(EPacketType::SendPacket);
	}

	SendPacket(int _ResType, int _PacketSize)
		: ServerProtocol(_PacketSize)
		, ResponseType(_ResType)
	{
		SetType(EPacketType::SendPacket);
	}

	void Serialize(ServerSerializer& _Ser) override
	{
		ServerProtocol::Serialize(_Ser);
		_Ser << ResponseType;
	}

	void DeSerialize(ServerSerializer& _Ser) override
	{
		ServerProtocol::DeSerialize(_Ser);
		_Ser >> ResponseType;
	}

public:
	// � ��Ŷ������ ���� �������� ����
	int ResponseType = -1;

};

class SendNValuePacket : public SendPacket
{
public:
	SendNValuePacket()
		:SendPacket(static_cast<int>(ERequestType::GetNValue))
	{

	}

	SendNValuePacket(int PacketSize, int _NValue)
		:SendPacket(static_cast<int>(ERequestType::GetNValue),PacketSize)
		,NValue(_NValue)
	{

	}

	void Serialize(ServerSerializer& _Ser) override
	{
		SendPacket::Serialize(_Ser);
		_Ser << NValue;
	}

	void DeSerialize(ServerSerializer& _Ser) override
	{
		SendPacket::DeSerialize(_Ser);
		_Ser >> NValue;
	}

public:
	// NValue ��
	int NValue = -1;
};
