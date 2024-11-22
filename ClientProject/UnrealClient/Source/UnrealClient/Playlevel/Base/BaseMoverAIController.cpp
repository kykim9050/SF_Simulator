// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/Base/BaseMoverAIController.h"

void ABaseMoverAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunBehaviorTree(BehaviorTree);
}
