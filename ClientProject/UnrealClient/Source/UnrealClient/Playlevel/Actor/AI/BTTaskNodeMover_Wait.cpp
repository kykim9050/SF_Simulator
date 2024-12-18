// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/Actor/AI/BTTaskNodeMover_Wait.h"
#include "BTTaskNodeMover_Wait.h"

EBTNodeResult::Type UBTTaskNodeMover_Wait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	EMoverState StateValue = GetCurState<EMoverState>(OwnerComp);

	// 현재 본인의 상태와 맞지 않다면 Failed
	if (StateValue != EMoverState::Wait)
	{
		return EBTNodeResult::Type::Failed;
	}

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNodeMover_Wait::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	UMoverData* MoverData = GetValueAsObject<UMoverData>(OwnerComp, TEXT("MoverData"));

	if (MoverData)
	{	
		int a = 0;
		// 만약 경로가 세팅되었다면
		//	ChangeState(OwnerComp, EMoverState::Idle);
		//	return;
	}
}


