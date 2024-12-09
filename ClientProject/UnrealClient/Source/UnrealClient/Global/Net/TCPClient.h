// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "GameFramework/Actor.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Networking.h"
#include "Global/GlobalFunctonLibrary.h"
#include "Global/Net/ClientProtocol.h"
#include "TCPClient.generated.h"

/**
 * TCP ����� �ְ��� Client Ŭ����
 */
UCLASS()
class UNREALCLIENT_API ATCPClient : public AActor
{
	GENERATED_BODY()
public:
	ATCPClient();
	virtual ~ATCPClient();

	/// <summary>
	/// Server�� ���� �ϱ� ���� �Լ�
	/// </summary>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable)
	bool ConnectToServer(const FString& _IPAddress, int32 _Port);

	/// <summary>
	/// ������ ������ ���� �Լ�
	/// </summary>
	/// <param name="_Data"></param>
	UFUNCTION(BlueprintCallable)
	void SendData(const FString& _Data);

	
	/// <summary>
	/// ������ ������ ���� �Լ� (FVutterArchive�� ����)
	/// </summary>
	/// <param name="_PacketData"></param>
	void SendData(const FBufferArchive& _PacketData);

	/// <summary>
	/// ��û ��Ŷ ���� �Լ�
	/// </summary>
	/// <param name="_RequestType"></param>
	UFUNCTION(BlueprintCallable)
	void SendRequestData(ERequestType _RequestType)
	{
		TSharedPtr<FBufferArchive> Packet = UClientPacketManager::CreateRequestPacket<FClientRequestPacket>(_RequestType);

		SendData(*Packet.Get());
	}

	/// <summary>
	/// ������ ������ ���� �Լ�
	/// </summary>
	/// <param name="_Data"></param>
	void RecvData();

protected:

private:

	/// <summary>
	/// Client���� ����� ����� ����
	/// </summary>
	FSocket* TCPClientSocket = nullptr;
};
