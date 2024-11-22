// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseMoverAIController.generated.h"

/**
 * Mover�� BaseAIController Ŭ����
 */
class UBehaviorTree;
UCLASS()
class UNREALCLIENT_API ABaseMoverAIController : public AAIController
{
	GENERATED_BODY()
public:

protected:
	/// <summary>
	/// Possess�Ǿ��� �� ����Ǵ� �Լ�
	/// </summary>
	/// <param name="InPawn"></param>
	void OnPossess(APawn* InPawn) override;

private:

	UPROPERTY(EditAnywhere, Category = "Property", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTree> BehaviorTree = nullptr;
};
