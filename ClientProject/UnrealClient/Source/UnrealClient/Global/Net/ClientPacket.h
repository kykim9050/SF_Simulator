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
UENUM()
enum class EPacketType : uint8
{
	GetNValuePacket,
};

USTRUCT()
struct UNREALCLIENT_API FGetNValuePacket : public FClientProtocol
{
	GENERATED_BODY()
public:


public:
	FGetNValuePacket()
	{
		SetType(EPacketType::GetNValuePacket);
	}

	FGetNValuePacket(uint32 _Size)
		:FClientProtocol(static_cast<uint32>(EPacketType::GetNValuePacket), _Size)
	{

	}
};
