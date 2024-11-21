// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimulatorManager.generated.h"

/*
* Simulation을 위해 GridFloor와 Mover를 관리 및 제어하는 클래스
*/
class UTestDataComponent;
class AGridPlatform;
UCLASS()
class UNREALCLIENT_API ASimulatorManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimulatorManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	/// <summary>
	/// GridPlatform을 Spawn하는 함수
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void SpawnGridPlatform(FVector _Pos = FVector(.0f, .0f, .0f), int _N = 1);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Test용 데이터 (로봇 아이디, 경로 정보 전달 용)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Test Prop", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTestDataComponent> TestDataComponent = nullptr;

	/// <summary>
	/// 블루프린트 상에서 생성할 GridPlatform 객체를 지정
	/// </summary>
	UPROPERTY(Editanywhere, Category = "Insert Parameter", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> GridPlatformClass = nullptr;

	/// <summary>
	/// GridPlatform의 포인터를 소유
	/// </summary>
	TObjectPtr<AGridPlatform> GridPlatform = nullptr;
};
