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

protected:

private:

	/// <summary>
	/// Client���� ����� ����� ����
	/// </summary>
	FSocket* TCPClientSocket = nullptr;
};
