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
};

USTRUCT()
struct UNREALCLIENT_API FRequestNPacket : public FClientProtocol
{
	GENERATED_BODY()
public:
	FRequestNPacket()
	{
		SetType(EPacketType::NValuePacket);
	}

	FRequestNPacket(uint32 _Size)
		:FClientProtocol(static_cast<uint32>(EPacketType::NValuePacket), _Size)
	{

	}
};