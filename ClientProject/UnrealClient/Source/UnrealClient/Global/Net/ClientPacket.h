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
UENUM()
enum class EPacketType : uint8
{
	ClientRequestPacket,
};

UENUM()
enum class ERequestType : uint8
{
	None,
	GetNValue,	// N�� ��û
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
	/// ��û Ÿ��
	/// </summary>
	int RequestType = -1;
};
