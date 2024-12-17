#pragma once
#include "ServerProtocol.h"
#include "Point.h"

// 설명 : Server 측 패킷 모음

enum class EPacketType
{
	None,
	NValuePacket = 100,		// N값 관련 패킷
	MoverCoursePacket,	// 이동체 경로관련 패킷
};

// NValue 요청 패킷
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

// NValue 응답 패킷
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
	// NValue 값
	int NValue = -1;
};

// 경로 요청 패킷
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
	int StartXPos = -1;
	int StartYPos = -1;
	int DestXPos = -1;
	int DestYPos = -1;
};

// 경로 응답 패킷
class SendMoverCoursePacket : public ServerProtocol
{
public:
	SendMoverCoursePacket()
	{
		SetType(EPacketType::MoverCoursePacket);
	}

	void Serialize(ServerSerializer& _Ser) override
	{
		ServerProtocol::Serialize(_Ser);
		_Ser << ID;
	}

	void DeSerialize(ServerSerializer& _Ser) override
	{
		ServerProtocol::DeSerialize(_Ser);
		_Ser >> ID;
	}

	void AddPathInfo(Point& _Pos)
	{
		AddPathInfo(_Pos.X, _Pos.Y);
	}

public:
	int ID = -1;
	std::vector<int> PathInfo;

private:
	void AddPathInfo(int _X, int _Y)
	{
		PathInfo.push_back(_X);
		PathInfo.push_back(_Y);
	}
};