#pragma once
#include "ServerProtocol.h"

// ���� : Server �� ��Ŷ ����

enum class EPacketType
{
	None,
	NValuePacket = 100,		// N�� ���� ��Ŷ
	MoverCoursePacket,	// �̵�ü ��ΰ��� ��Ŷ
};

// NValue ��û ��Ŷ
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

// NValue ���� ��Ŷ
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

// ��� ��û ��Ŷ
class RecvMoverCoursePacket : public ServerProtocol
{
public:
	RecvMoverCoursePacket()
	{
		SetType(EPacketType::MoverCoursePacket);
	}

	void Serialize(ServerSerializer& _Ser) override
	{
		ServerProtocol::Serialize(_Ser);
		_Ser << ID;
		_Ser << StartXPos;
		_Ser << StartYPos;
		_Ser << DestXPos;
		_Ser << DestYPos;
	}

	void DeSerialize(ServerSerializer& _Ser) override
	{
		ServerProtocol::DeSerialize(_Ser);
		_Ser >> ID;
		_Ser >> StartXPos;
		_Ser >> StartYPos;
		_Ser >> DestXPos;
		_Ser >> DestYPos;
	}

public:
	int ID = -1;
	double StartXPos = -1.0;
	double StartYPos = -1.0;
	double DestXPos = -1.0;
	double DestYPos = -1.0;
};