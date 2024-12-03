// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ClientProtocol.generated.h"

/**
 * 
 */
USTRUCT()
struct UNREALCLIENT_API FClientProtocol
{
	GENERATED_BODY()

public:
	uint32 Type;
	uint32 Size;

	FClientProtocol()
		:Type(0)
		,Size(0)
	{

	}

	FClientProtocol(uint32 _Type, uint32 _Size)
		:Type(_Type)
		, Size(_Size)
	{

	}

	friend FArchive& operator<<(FArchive& Ar, FClientProtocol& Header)
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
