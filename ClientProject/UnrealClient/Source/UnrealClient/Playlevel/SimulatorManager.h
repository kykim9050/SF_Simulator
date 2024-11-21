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
class AMover;
class APawn;
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
	/// GridPlatform을 원하는 크기에 맞게 Spawn하는 함수
	/// _Pos : World에서 생성하고자 하는 위치 (중심)
	/// _N : 서버로 부터 수신 받은 N값
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void SpawnGridPlatform(FVector _Pos = FVector(.0f, .0f, .0f), int _N = 1);

	UFUNCTION(BlueprintCallable)
	void SpawnMover(FVector _Pos = FVector(.0f, .0f, .0f));

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetIsMoversSpawnable()
	{
		bIsMoversSpawnable = true;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Test용 데이터 (로봇 아이디, 경로 정보 전달 용)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Test Prop", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTestDataComponent> TestDataComponent = nullptr;

	/// <summary>
	/// 블루프린트 상에서 생성할 GridPlatform 객체를 지정, 클래스 정보 저장
	/// </summary>
	UPROPERTY(Editanywhere, Category = "Insert Parameter", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> GridPlatformClass = nullptr;

	/// <summary>
	/// GridPlatform의 포인터를 소유
	/// </summary>
	TObjectPtr<AGridPlatform> GridPlatform = nullptr;

	/// <summary>
	/// 블루프린트 상에서 생성할 Mover 객체를 지정, 클래스 정보 저장
	/// </summary>
	UPROPERTY(Editanywhere, Category = "Insert Parameter", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APawn> MoverClass = nullptr;

	/// <summary>
	/// 생성될 Mover 객체들 정보 소유
	/// </summary>
	TArray<TObjectPtr<AMover>> Movers = TArray<TObjectPtr<AMover>>();
	
	/// <summary>
	/// Mover를 연속적으로 출력하기 위한 시그널 변수
	/// </summary>
	bool bIsMoversSpawnable = false;






	/// <summary>
	/// Test N값
	/// </summary>
	int NValue = 1;
};
