// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Playlevel/Base/BTTaskNodeBase_Mover.h"
#include "BTTaskNodeMover_Decel.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCLIENT_API UBTTaskNodeMover_Decel : public UBTTaskNodeBase_Mover
{
	GENERATED_BODY()
public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds) override;
};
