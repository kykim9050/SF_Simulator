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
#include "Global/Net/ClientPacketManager.h"
#include "Global/Net/ClientInterpreter.h"
#include "TCPClient.generated.h"

/**
 * TCP 통신을 주관할 Client 클래스
 */
UCLASS()
class UNREALCLIENT_API ATCPClient : public AActor
{
	GENERATED_BODY()
public:
	ATCPClient();
	virtual ~ATCPClient();

	/// <summary>
	/// Server와 접속 하기 위한 함수
	/// </summary>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable)
	bool ConnectToServer(const FString& _IPAddress, int32 _Port);

	/// <summary>
	/// 데이터 전송을 위한 함수 (FVutterArchive형 전달)
	/// </summary>
	/// <param name="_PacketData"></param>
	void SendData(const FBufferArchive& _PacketData);

	/// <summary>
	/// 요청 패킷 생성 함수
	/// </summary>
	/// <param name="_RequestType"></param>
	UFUNCTION(BlueprintCallable)
	void SendRequestData(EPacketType _RequestType)
	{
		TSharedPtr<FBufferArchive> Packet = UClientPacketManager::CreateRequestPacket(_RequestType);

		SendData(*Packet.Get());
	}

	/// <summary>
	/// 데이터 수신을 위한 함수
	/// </summary>
	/// <param name="_Data"></param>
	void RecvData();

protected:

private:
	void ClientPacketInit(TObjectPtr<UClientInterpreter> _Interpret);

private:
	/// <summary>
	/// Client에서 통신을 담당할 소켓
	/// </summary>
	FSocket* TCPClientSocket = nullptr;

	/// <summary>
	/// 수신용 패킷 해석자
	/// </summary>
	UPROPERTY()
	TObjectPtr<UClientInterpreter> Interpret = nullptr;
};