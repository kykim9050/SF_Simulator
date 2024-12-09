// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Networking.h"
#include "Global/Net/ClientPacket.h"
#include "ClientPacketManager.generated.h"

/**
 * Ŭ���̾�Ʈ �� ��Ŷ ���� �Ŵ���
 */
UCLASS()
class UNREALCLIENT_API UClientPacketManager : public UObject
{
	GENERATED_BODY()
public:
	
	template<typename EnumType>
	static TSharedPtr<FBufferArchive> CreateRequestPacket(EnumType _RequestType)
	{
		return CreatePacket<FClientRequestPacket>(static_cast<int32>(_RequestType));
	}

	template<typename PacketType>
	static TSharedPtr<FBufferArchive> CreatePacket(const int32 _Value)
	{
		FString IntStr = FString::FromInt(_Value);

		return CreatePacket<PacketType>(IntStr);
	}


	template<typename PacketType>
	static TSharedPtr<FBufferArchive> CreatePacket(const FString& _Data = FString(""))
	{
		FTCHARToUTF8 Convert(*_Data);
		FArrayWriter WriteArray = FArrayWriter();

		WriteArray.Serialize((UTF8CHAR*)Convert.Get(), Convert.Length());
		TSharedPtr<FBufferArchive> Packet = CreatePacket<PacketType>(WriteArray.GetData(), WriteArray.Num());

		return Packet;
	}


protected:

private:
	template<typename PacketType>
	static TSharedPtr<FBufferArchive> CreatePacket(const uint8* _InPayload, int32 _InPayloadSize)
	{
		PacketType Header(_InPayloadSize);

		TSharedPtr<FBufferArchive> Packet = MakeShareable(new FBufferArchive());

		(*Packet) << Header;

		Packet->Append(_InPayload, _InPayloadSize);

		return Packet;
	}

};
