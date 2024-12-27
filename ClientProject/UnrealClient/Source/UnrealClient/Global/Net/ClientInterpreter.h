// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Global/Net/ClientProtocol.h"
#include "ClientInterpreter.generated.h"

/**
 * ��Ŷ ������ ���� ��Ŷ�� �ؼ��ϴ� Ŭ����
 */

DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FRecvBaseProtocol>, FConvertPacketHandlerDelegate, FMemoryArchive&)
DECLARE_DELEGATE_OneParam(FPacketHandlerDelegate, TSharedPtr<FRecvBaseProtocol>)


UCLASS()
class UNREALCLIENT_API UClientInterpreter : public UObject
{
	GENERATED_BODY()
public:
	/// <summary>
	/// Ư�� ��Ŷ �����ͷ� ��ȯ
	/// </summary>
	/// <param name="_Type"></param>
	/// <param name="_ReadMem"></param>
	/// <returns></returns>
	TSharedPtr<FRecvBaseProtocol> ConvertProtocol(int32 _Type, FMemoryArchive& _ReadMem);

	/// <summary>
	/// Ư�� ��Ŷ�� ���� ������ Handler ȣ��
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
		if (true == PacketHandlers.Contains(_Type))
		{
			UE_LOG(LogType, Fatal, TEXT("This handler is already registered."));
			return;
		}

		ConvertPacketHandlers.Add(_Type, FConvertPacketHandlerDelegate::CreateLambda([=](FMemoryArchive& _ReadMem)->TSharedPtr<FRecvBaseProtocol> {
			TSharedPtr<PacketType> NewPacket = MakeShared<PacketType>();
			_ReadMem << *NewPacket;
			return NewPacket;
			})
		);

		PacketHandlers.Add(_Type, FPacketHandlerDelegate::CreateLambda([=](TSharedPtr<FRecvBaseProtocol> _Packet) {
			TSharedPtr<PacketType> ConvertPacket = StaticCastSharedPtr<PacketType>(_Packet);

			if (!ConvertPacket.IsValid())
			{
				UE_LOG(LogType, Fatal, TEXT("Ÿ���� ��ġ���� �ʴ� ��Ŷ�Դϴ�."));
				return;
			}

			_CallBack(ConvertPacket);
			})
		);
	}

protected:

private:
	/// <summary>
	/// ��Ŷ�� ��ȯ�� �żҵ带 �����ϴ� �ڷᱸ��
	/// </summary>
	TMap<int32, FConvertPacketHandlerDelegate> ConvertPacketHandlers;

	/// <summary>
	/// ��Ŷ�� ���� ������ �żҵ带 �����ϴ� �ڷᱸ��
	/// </summary>
	TMap<int32, FPacketHandlerDelegate> PacketHandlers;

};
