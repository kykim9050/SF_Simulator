// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Net/ClientProtocol.h"
#include "ClientPacket.generated.h"
/**
 * TCP ���� ��� ��Ŷ ����
 */

/// <summary>
/// ��Ŷ Ÿ�� ���� Enum
/// </summary>
UENUM(BlueprintType)
enum class EPacketType : uint8
{
	None,
	NValuePacket = 100,		// N�� ���� ��Ŷ
	MoverCoursePacket,	// �̵�ü ��ΰ��� ��Ŷ
};

/// <summary>
/// N��û�� ��Ŷ
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
/// Mover�� Path ��û�� ��Ŷ
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

public:
};

/// <summary>
/// N ���ſ� ��Ŷ
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
/// Path ���ſ� ��Ŷ
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

		int32 TempValue = -1;
		for (int32 i = 0; i < Packet.PathInfoSize; i++)
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