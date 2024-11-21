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
	/// GridPlatform�� Spawn�ϴ� �Լ�
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void SpawnGridPlatform(FVector _Pos = FVector(.0f, .0f, .0f), int _N = 1);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Test�� ������ (�κ� ���̵�, ��� ���� ���� ��)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Test Prop", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTestDataComponent> TestDataComponent = nullptr;

	/// <summary>
	/// �������Ʈ �󿡼� ������ GridPlatform ��ü�� ����
	/// </summary>
	UPROPERTY(Editanywhere, Category = "Insert Parameter", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> GridPlatformClass = nullptr;

	/// <summary>
	/// GridPlatform�� �����͸� ����
	/// </summary>
	TObjectPtr<AGridPlatform> GridPlatform = nullptr;
};
