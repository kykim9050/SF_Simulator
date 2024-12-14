// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ClientProtocol.generated.h"

/**
 * 
 */
USTRUCT()
struct UNREALCLIENT_API FMessageHeader
{
	GENERATED_BODY()

public:
	uint32 Type;
	uint32 Size;

public:
	FMessageHeader()
		:Type(0)
		,Size(0)
	{

	}

	FMessageHeader(uint32 _Type, uint32 _Size)
		:Type(_Type)
		, Size(_Size)
	{

	}

	friend FArchive& operator<<(FArchive& Ar, FMessageHeader& Header)
	{
		Ar << Header.Type;
		Ar << Header.Size;

		return Ar;
	}

	template<typename PacketType>
	void SetType(PacketType _Type)
	{
		Type = static_cast<uint32>(_Type);
	}
};

/// <summary>
/// 수신 전용 패킷의 타입 확인용
/// </summary>
USTRUCT()
struct UNREALCLIENT_API FRecvBaseProtocol
{
	GENERATED_BODY()
public:
	uint32 Type;

public:
	FRecvBaseProtocol()
		:Type(0)
	{

	}

	template<typename PacketType>
	void SetType(PacketType _Type)
	{
		Type = static_cast<uint32>(_Type);
	}

	FORCEINLINE int32 GetType() const
	{
		return Type;
	}
};