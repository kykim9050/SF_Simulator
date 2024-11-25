// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Base/GlobalGameMode.h"
#include "Global/Net/TCPClient.h"
#include "ClientPlayGameMode.generated.h"

/**
 * ClientPlay ������ GameMode
 */
class ASimulatorManager;
UCLASS()
class UNREALCLIENT_API AClientPlayGameMode : public AGlobalGameMode
{
	GENERATED_BODY()
public:

protected:
	virtual void BeginPlay() override;

private:
	/// <summary>
	/// ���� �÷��� ��忡�� ������ ASimulatorManager�� �ּ�
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Manager", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ASimulatorManager> MainSimulator = nullptr;

	/// <summary>
	/// GameMode �������Ʈ �󿡼� ������ �Ŵ��� �������Ʈ ��ü�� ����
	/// </summary>
	UPROPERTY(Editanywhere, Category = "Manager", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> MainSimulatorClass = nullptr;

	/// <summary>
	/// ������ TCPClient �������Ʈ ��ü�� ����
	/// </summary>
	UPROPERTY(Editanywhere, Category = "Networking", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> TCPClientClass = nullptr;
	
	/// <summary>
	/// ����� ���
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ATCPClient> TCPClient = nullptr;
};
