// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "TCPClient.generated.h"

/**
 * TCP ����� �ְ��� Client Ŭ����
 */
UCLASS()
class UNREALCLIENT_API UTCPClient : public UObject
{
	GENERATED_BODY()
public:
	UTCPClient();
	virtual ~UTCPClient();

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
	FSocket* ClientSocket = nullptr;
};
