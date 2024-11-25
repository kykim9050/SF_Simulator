// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/Actor/AI/BTTaskNodeMover_Decel.h"

EBTNodeResult::Type UBTTaskNodeMover_Decel::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	EMoverState StateValue = GetCurState<EMoverState>(OwnerComp);

	// 현재 본인의 상태와 맞지 않다면 Failed
	if (StateValue != EMoverState::Decel)
	{
		return EBTNodeResult::Type::Failed;
	}

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNodeMover_Decel::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	AMover* Mover = GetSelfActor<AMover>(OwnerComp);

	UMoverData* MoverData = GetValueAsObject<UMoverData>(OwnerComp, TEXT("MoverData"));

	if (nullptr != Mover)
	{
		FVector CurPos = Mover->GetActorLocation();
		CurPos.Z = .0;
		int CurIdx = MoverData->CurWaypointIdx;
		FVector DestPos = FVector(MoverData->WayPointsInfo[CurIdx].X, MoverData->WayPointsInfo[CurIdx].Y, .0);

		FVector Dir = DestPos - CurPos;
		Dir.Normalize();

		// 속도 감속 (감속도 고려)
		MoverData->CurVelocity = FMath::Max(MoverData->CurVelocity - MoverData->Data->Accel * DeltaSeconds, .0);

		if (.0 >= MoverData->CurVelocity)
		{
			++MoverData->CurWaypointIdx;
			MoverData->CurVelocity = .0;
			ChangeState(OwnerComp, EMoverState::Idle);
			return;
		}

		// 감속도 적용한 속도
		Mover->AddActorWorldOffset(DeltaSeconds * Dir * MoverData->CurVelocity);
	}
}