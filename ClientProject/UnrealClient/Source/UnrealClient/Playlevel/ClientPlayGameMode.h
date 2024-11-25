// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Base/GlobalGameMode.h"
#include "Global/Net/TCPClient.h"
#include "ClientPlayGameMode.generated.h"

/**
 * ClientPlay 레벨용 GameMode
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
	/// 실제 플레이 모드에서 생성된 ASimulatorManager의 주소
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Manager", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ASimulatorManager> MainSimulator = nullptr;

	/// <summary>
	/// GameMode 블루프린트 상에서 생성할 매니저 블루프린트 객체를 지정
	/// </summary>
	UPROPERTY(Editanywhere, Category = "Manager", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> MainSimulatorClass = nullptr;

	/// <summary>
	/// 생성할 TCPClient 블루프린트 객체를 지정
	/// </summary>
	UPROPERTY(Editanywhere, Category = "Networking", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> TCPClientClass = nullptr;
	
	/// <summary>
	/// 통신을 담당
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ATCPClient> TCPClient = nullptr;
};
