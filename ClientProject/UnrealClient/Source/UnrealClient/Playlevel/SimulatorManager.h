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
	
	void SpawnGridPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Test�� ������ (�κ� ���̵�, ��� ���� ���� ��)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Test Prop", meta = (AllowPrivateAccess = "true"))
	UTestDataComponent* TestDataComponent = nullptr;

	UPROPERTY()
	TWeakObjectPtr<AGridPlatform> GridPlatform = nullptr;
};
