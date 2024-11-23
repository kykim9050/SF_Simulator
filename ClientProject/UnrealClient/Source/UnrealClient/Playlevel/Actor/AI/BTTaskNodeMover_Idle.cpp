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
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	AMover* Mover = GetSelfActor<AMover>(OwnerComp);
	
	UMoverData* MoverData = GetValueAsObject<UMoverData>(OwnerComp, TEXT("MoverData"));

	if (nullptr != Mover)
	{
		FVector CurPos = Mover->GetActorLocation();
		CurPos.Z = .0;
		int CurIdx = MoverData->CurWaypointIdx;

		// 이동해야할 목표 Idx가 아직 존재할 때
		if (CurIdx < MoverData->WayPointsInfo.Num())
		{
			FVector DestPos = FVector(MoverData->WayPointsInfo[CurIdx].X, MoverData->WayPointsInfo[CurIdx].Y, .0);

			UMainGameInstance* Inst = UGlobalFunctonLibrary::GetMainGameInstance(GetWorld());
			
			if (true == IsDestDirSameToCurDir(CurPos, DestPos, MoverData->Dir))
			{
				// Accel 조건
				ChangeState(OwnerComp, EMoverState::Accel);
				return;
			}
			else
			{
				// 회전 조건
				ChangeState(OwnerComp, EMoverState::Rotate);
				return;
			}
		}
		else
		{
			// 도착
			ChangeState(OwnerComp, EMoverState::Finish);
			return;
		}
	}
}