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