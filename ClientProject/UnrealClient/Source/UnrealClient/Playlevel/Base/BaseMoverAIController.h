// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseMoverAIController.generated.h"

/**
 * Mover용 BaseAIController 클래스
 */
class UBehaviorTree;
UCLASS()
class UNREALCLIENT_API ABaseMoverAIController : public AAIController
{
	GENERATED_BODY()
public:

protected:
	/// <summary>
	/// Possess되었을 때 실행되는 함수
	/// </summary>
	/// <param name="InPawn"></param>
	void OnPossess(APawn* InPawn) override;

private:

	UPROPERTY(EditAnywhere, Category = "Property", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTree> BehaviorTree = nullptr;
};
