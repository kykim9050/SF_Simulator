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
	ClientRequestPacket,
};

UENUM()
enum class ERequestType : uint8
{
	None,
	GetNValue,	// N값 요청
};

USTRUCT()
struct UNREALCLIENT_API FClientRequestPacket : public FClientProtocol
{
	GENERATED_BODY()
public:
	FClientRequestPacket()
	{
		SetType(EPacketType::ClientRequestPacket);
	}

	FClientRequestPacket(uint32 _Size)
		:FClientProtocol(static_cast<uint32>(EPacketType::ClientRequestPacket), _Size)
	{

	}

public:
	/// <summary>
	/// 요청 타입
	/// </summary>
	int RequestType = -1;
};
