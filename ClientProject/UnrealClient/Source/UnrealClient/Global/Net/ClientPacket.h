// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Net/ClientProtocol.h"
#include "ClientPacket.generated.h"
/**
 * TCP 소켓 통신 패킷 모음
 */

/// <summary>
/// 패킷 타입 관련 Enum
/// </summary>
UENUM(BlueprintType)
enum class EPacketType : uint8
{
	None,
	NValuePacket = 100,		// N값 관련 패킷
	MoverCoursePacket,	// 이동체 경로관련 패킷
	InfoSavePacket,		// 서버에 전달할 저장할 정보관련 패킷
};

/// <summary>
/// N요청용 패킷
/// </summary>
USTRUCT()
struct UNREALCLIENT_API FRequestNPacket : public FMessageHeader
{
	GENERATED_BODY()
public:
	FRequestNPacket()
	{
		SetType(EPacketType::NValuePacket);
	}

	FRequestNPacket(uint32 _Size)
		:FMessageHeader(static_cast<uint32>(EPacketType::NValuePacket), _Size)
	{

	}
};

/// <summary>
/// Mover의 Path 요청용 패킷
/// </summary>
USTRUCT()
struct UNREALCLIENT_API FRequestPathPacket : public FMessageHeader
{
	GENERATED_BODY()
public:
	FRequestPathPacket()
	{
		SetType(EPacketType::MoverCoursePacket);
	}

	FRequestPathPacket(uint32 _Size)
		:FMessageHeader(static_cast<uint32>(EPacketType::MoverCoursePacket), _Size)
	{

	}
};

/// <summary>
/// Mover의 목적지 도착시 저장할 정보 전달 패킷
/// </summary>
USTRUCT()
struct UNREALCLIENT_API FRequestInfoSavePacket : public FMessageHeader
{
	GENERATED_BODY()
public:
	FRequestInfoSavePacket()
	{
		SetType(EPacketType::InfoSavePacket);
	}

	FRequestInfoSavePacket(uint32 _Size)
		:FMessageHeader(static_cast<uint32>(EPacketType::InfoSavePacket), _Size)
	{

	}
};

/// <summary>
/// N 수신용 패킷
/// </summary>
USTRUCT()
struct UNREALCLIENT_API FRecvNPacket: public FRecvBaseProtocol
{
	GENERATED_BODY()
public:
	FRecvNPacket()
		: N(-1)
	{
		SetType(EPacketType::NValuePacket);
	}

	friend FArchive& operator<<(FArchive& Ar, FRecvNPacket& Packet)
	{
		Ar << Packet.N;

		return Ar;
	}

public:
	int32 N = -1;
};

/// <summary>
/// Path 수신용 패킷
/// </summary>
USTRUCT()
struct UNREALCLIENT_API FRecvPathPacket : public FRecvBaseProtocol
{
	GENERATED_BODY()
public:
	FRecvPathPacket()
		: ID(-1)
	{
		SetType(EPacketType::MoverCoursePacket);
	}

	friend FArchive& operator<<(FArchive& Ar, FRecvPathPacket& Packet)
	{
		Ar << Packet.ID;
		Ar << Packet.PathInfoSize;

		Packet.PathInfo.Reserve(Packet.PathInfoSize);
		int32 TempValue = -1;
		for (int32 i = 0; i < Packet.PathInfoSize; ++i)
		{
			Ar << TempValue;
			Packet.PathInfo.Add(TempValue);
		}
		return Ar;
	}

public:
	int32 ID = -1;
	int32 PathInfoSize = -1;
	TArray<int32> PathInfo;
};

/// <summary>
/// 정보 저장 관련 응답 패킷
/// </summary>
USTRUCT()
struct FRecvInfoSavePacket : public FRecvBaseProtocol
{
	GENERATED_BODY()
public:
	FRecvInfoSavePacket()
		:ID(-1)
	{
		SetType(EPacketType::InfoSavePacket);
	}

	friend FArchive& operator<<(FArchive& Ar, FRecvInfoSavePacket& Packet)
	{
		Ar << Packet.ID;

		return Ar;
	}

public:
	int32 ID = -1;
};