// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "TCPClient.generated.h"

/**
 * TCP 통신을 주관할 Client 클래스
 */
UCLASS()
class UNREALCLIENT_API UTCPClient : public UObject
{
	GENERATED_BODY()
public:
	UTCPClient();
	virtual ~UTCPClient();

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
	FSocket* ClientSocket = nullptr;
};
