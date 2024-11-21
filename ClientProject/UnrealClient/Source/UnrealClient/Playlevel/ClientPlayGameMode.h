// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Base/GlobalGameMode.h"
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
	ASimulatorManager* MainSimulator = nullptr;

	/// <summary>
	/// GameMode �������Ʈ �󿡼� ������ �Ŵ��� �������Ʈ ��ü�� ����
	/// </summary>
	UPROPERTY(Editanywhere, Category = "Manager", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> MainSimulatorClass = nullptr;
};
