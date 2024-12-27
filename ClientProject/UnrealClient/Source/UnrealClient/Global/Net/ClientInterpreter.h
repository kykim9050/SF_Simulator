// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Global/Net/ClientProtocol.h"
#include "ClientInterpreter.generated.h"

/**
 * 패킷 종류에 따라 패킷을 해석하는 클래스
 */

DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FRecvBaseProtocol>, FConvertPacketHandlerDelegate, FMemoryArchive&)
DECLARE_DELEGATE_OneParam(FPacketHandlerDelegate, TSharedPtr<FRecvBaseProtocol>)

/// <summary>
/// 패킷을 해석하는 핸들러가 포함되어있는 구조체
/// </summary>
USTRUCT()
struct FConvertPacketHandlerMap
{
	GENERATED_BODY()
public:
	/// <summary>
	/// 패킷을 변환할 매소드를 포함하는 자료구조
	/// </summary>
	TMap<int32, FConvertPacketHandlerDelegate> Handlers;
};

/// <summary>
/// 특정 패킷의 핸들러 매소드가 저장되어있는 구조체
/// </summary>
USTRUCT()
struct FPacketHandlerMap
{
	GENERATED_BODY()
public:
	/// <summary>
	/// 패킷에 따라서 수행할 매소드를 포함하는 자료구조
	/// </summary>
	TMap<int32, FPacketHandlerDelegate> Handlers;
};

UCLASS()
class UNREALCLIENT_API UClientInterpreter : public UObject
{
	GENERATED_BODY()
public:
	/// <summary>
	/// 특정 패킷 데이터로 변환
	/// </summary>
	/// <param name="_Type"></param>
	/// <param name="_ReadMem"></param>
	/// <returns></returns>
	TSharedPtr<FRecvBaseProtocol> ConvertProtocol(int32 _Type, FMemoryArchive& _ReadMem);

	/// <summary>
	/// 특정 패킷에 따라 실행할 Handler 호출
	/// </summary>
	/// <param name="_Packet"></param>
	void ProcessPacket(TSharedPtr<FRecvBaseProtocol> _Packet);

	template<typename PacketType>
	void AddHandler(TFunction<void(TSharedPtr<PacketType>)> _CallBack)
	{
		PacketType PacketInstance;
		int Type = static_cast<int>(PacketInstance.GetType());
		AddHandler(Type, _CallBack);
	}

	template<typename PacketType>
	void AddHandler(int _Type, TFunction<void(TSharedPtr<PacketType>)> _CallBack)
	{
		if (true == PacketHandlers.Handlers.Contains(_Type))
		{
			UE_LOG(LogType, Fatal, TEXT("This handler is already registered."));
			return;
		}

		ConvertPacketHandlers.Handlers.Add(_Type, FConvertPacketHandlerDelegate::CreateLambda([=](FMemoryArchive& _ReadMem)->TSharedPtr<FRecvBaseProtocol> {
			TSharedPtr<PacketType> NewPacket = MakeShared<PacketType>();
			_ReadMem << *NewPacket;
			return NewPacket;
			})
		);

		PacketHandlers.Handlers.Add(_Type, FPacketHandlerDelegate::CreateLambda([=](TSharedPtr<FRecvBaseProtocol> _Packet) {
			TSharedPtr<PacketType> ConvertPacket = StaticCastSharedPtr<PacketType>(_Packet);

			if (!ConvertPacket.IsValid())
			{
				UE_LOG(LogType, Fatal, TEXT("타입이 일치하지 않는 패킷입니다."));
				return;
			}

			_CallBack(ConvertPacket);
			})
		);
	}

protected:

private:
	UPROPERTY()
	FConvertPacketHandlerMap ConvertPacketHandlers;

	UPROPERTY()
	FPacketHandlerMap PacketHandlers;
	
};
