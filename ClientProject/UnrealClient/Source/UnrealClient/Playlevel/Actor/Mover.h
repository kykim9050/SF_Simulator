// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Global/Base/ObjectID.h"
#include "Mover.generated.h"

/*
* 이동체 클레스
*/
class UStaticMeshComponent;
class UArrowComponent;
class ASimulatorManager;
UCLASS()
class UNREALCLIENT_API AMover : public APawn, public ObjectID
{
	GENERATED_BODY()

	friend ASimulatorManager;

public:
	// Sets default values for this pawn's properties
	AMover();

	void SetTargetPos(FVector _TargetPos)
	{
		TargetPos = _TargetPos;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> MoverMeshComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Property", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> HedingComponent = nullptr;

	FVector TargetPos = FVector();
};
