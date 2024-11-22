// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/Actor/AI/BTTaskNodeMover_Accel.h"
#include "Playlevel/Actor/Mover.h"
#include "Playlevel/Base/BaseMoverAIController.h"

EBTNodeResult::Type UBTTaskNodeMover_Accel::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNodeMover_Accel::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	AMover* Mover = GetSelfActor<AMover>(OwnerComp);
	if (nullptr != Mover)
	{
		Mover->GetAIController()->MoveToLocation(FVector(.0f, .0f, 50.f));
	}
}
