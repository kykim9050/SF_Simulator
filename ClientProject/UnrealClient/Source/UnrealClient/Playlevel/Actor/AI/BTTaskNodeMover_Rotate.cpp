// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/Actor/AI/BTTaskNodeMover_Rotate.h"

EBTNodeResult::Type UBTTaskNodeMover_Rotate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	EMoverState StateValue = GetCurState<EMoverState>(OwnerComp);

	// ���� ������ ���¿� ���� �ʴٸ� Failed
	if (StateValue != EMoverState::Rotate)
	{
		return EBTNodeResult::Type::Failed;
	}

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNodeMover_Rotate::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	AMover* Mover = GetSelfActor<AMover>(OwnerComp);
	if (nullptr != Mover)
	{
		Mover->AddActorLocalRotation((DeltaSeconds * FQuat(FRotator(.0f, 1.0f, .0f))));
	}
}