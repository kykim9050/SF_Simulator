// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/Actor/AI/BTTaskNodeMover_Accel.h"

EBTNodeResult::Type UBTTaskNodeMover_Accel::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	EMoverState StateValue = GetCurState<EMoverState>(OwnerComp);

	// 현재 본인의 상태와 맞지 않다면 Failed
	if (StateValue != EMoverState::Accel)
	{
		return EBTNodeResult::Type::Failed;
	}

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNodeMover_Accel::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);
	
	AMover* Mover = GetSelfActor<AMover>(OwnerComp);
	if (nullptr != Mover)
	{
		Mover->GetCharacterMovement()->MoveSmooth(FVector(10.0f, 0.0f, 0.0f), DeltaSeconds);
	}
}
