// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/Actor/AI/BTTaskNodeMover_Finish.h"

EBTNodeResult::Type UBTTaskNodeMover_Finish::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	EMoverState StateValue = GetCurState<EMoverState>(OwnerComp);

	// ���� ������ ���¿� ���� �ʴٸ� Failed
	if (StateValue != EMoverState::Finish)
	{
		return EBTNodeResult::Type::Failed;
	}

	AMover* Mover = GetSelfActor<AMover>(OwnerComp);
	
	if (nullptr != Mover)
	{
		Mover->AllowDestroy();

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNodeMover_Finish::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	//DestroyTime -= DeltaSeconds;

	//if (0.0f >= DestroyTime)
	//{
	//	AMover* Mover = GetSelfActor<AMover>(OwnerComp);

	//	if (nullptr != Mover)
	//	{
	//		Mover->AllowDistroy();
	//	}
	//}
}