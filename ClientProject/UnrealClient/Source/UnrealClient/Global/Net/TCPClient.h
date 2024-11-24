// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "GameFramework/Actor.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Networking.h"
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

protected:

private:

	/// <summary>
	/// Client에서 통신을 담당할 소켓
	/// </summary>
	FSocket* TCPClientSocket = nullptr;
};
