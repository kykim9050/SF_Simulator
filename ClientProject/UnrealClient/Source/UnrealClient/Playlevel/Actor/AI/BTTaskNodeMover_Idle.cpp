// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/Actor/AI/BTTaskNodeMover_Idle.h"

EBTNodeResult::Type UBTTaskNodeMover_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	EMoverState StateValue = GetCurState<EMoverState>(OwnerComp);

	// 현재 본인의 상태와 맞지 않다면 Failed
	if (StateValue != EMoverState::Idle)
	{
		return EBTNodeResult::Type::Failed;
	}

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNodeMover_Idle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	AMover* Mover = GetSelfActor<AMover>(OwnerComp);
	
	UMoverData* MoverData = GetValueAsObject<UMoverData>(OwnerComp, TEXT("MoverData"));


	if (nullptr != Mover)
	{
		FVector CurPos = Mover->GetActorLocation();
		CurPos.Z = .0;
		FVector DestPos = FVector(MoverData->WayPointsInfo[3].X, MoverData->WayPointsInfo[3].X, .0);
	
		UMainGameInstance* Inst = UGlobalFunctonLibrary::GetMainGameInstance(GetWorld());

		// Accel 조건
		// 자신의 위치와 목표지점 위치의 거리 차이가 발생했을 때
		if (50.0f <= Inst->DistanceToDestPos2D(CurPos, DestPos))
		{
			ChangeState(OwnerComp, EMoverState::Accel);
			return;
		}
		// Idx를 1 추가하고
		// Accel로 상태를 바꾼다
	}

	// Stop 조건

	// Rotate 조건

	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);
}