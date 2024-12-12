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
	// 어떤 패킷인지에 대한 종류관련 변수
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
	// NValue 값
	int NValue = -1;
};
