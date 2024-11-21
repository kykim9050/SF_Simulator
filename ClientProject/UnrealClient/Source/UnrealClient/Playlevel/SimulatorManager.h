// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimulatorManager.generated.h"

/*
* Simulation�� ���� GridFloor�� Mover�� ���� �� �����ϴ� Ŭ����
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
	/// GridPlatform�� ���ϴ� ũ�⿡ �°� Spawn�ϴ� �Լ�
	/// _Pos : World���� �����ϰ��� �ϴ� ��ġ (�߽�)
	/// _N : ������ ���� ���� ���� N��
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void SpawnGridPlatform(FVector _Pos = FVector(.0f, .0f, .0f));

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
	/// <summary>
	/// Mover Spawn�� ������ �����ϴ� �Լ�
	/// </summary>
	/// <param name="_DeltaTime"></param>
	void SpawnMoverRepeatedly(float _DeltaTime);

	/// <summary>
	/// N�� ũ�⿡ �°� MoverSpawnTimes�� �迭 ��ҿ� ũ�⸦ �����ϴ� �Լ�
	/// </summary>
	void InitMoverSpawnTimes(int _N);

private:
	// Test�� ������ (�κ� ���̵�, ��� ���� ���� ��)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Test Prop", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTestDataComponent> TestDataComponent = nullptr;

	/// <summary>
	/// �������Ʈ �󿡼� ������ GridPlatform ��ü�� ����, Ŭ���� ���� ����
	/// </summary>
	UPROPERTY(Editanywhere, Category = "Insert Parameter", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> GridPlatformClass = nullptr;

	/// <summary>
	/// GridPlatform�� �����͸� ����
	/// </summary>
	TObjectPtr<AGridPlatform> GridPlatform = nullptr;

	/// <summary>
	/// �������Ʈ �󿡼� ������ Mover ��ü�� ����, Ŭ���� ���� ����
	/// </summary>
	UPROPERTY(Editanywhere, Category = "Insert Parameter", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APawn> MoverClass = nullptr;

	/// <summary>
	/// ������ Mover ��ü�� ���� ����
	/// </summary>
	TArray<TObjectPtr<AMover>> Movers = TArray<TObjectPtr<AMover>>();
	
	/// <summary>
	/// 
	/// </summary>
	TArray<float> MoverSpawnTimes = TArray<float>({ 0.0f, 1.0f, 2.0f });

	/// <summary>
	/// �������� �޾ƿ� N��
	/// </summary>
	int NValue = 1;

	/// <summary>
	/// Mover�� ���������� ����ϱ� ���� �ñ׳� ����
	/// </summary>
	bool bIsMoversSpawnable = false;
};
