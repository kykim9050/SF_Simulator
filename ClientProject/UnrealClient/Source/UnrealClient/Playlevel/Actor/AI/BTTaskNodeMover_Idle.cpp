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


	AMover* Mover = GetSelfActor<AMover>(OwnerComp);
	UMoverData* MoverData = GetValueAsObject<UMoverData>(OwnerComp, TEXT("MoverData"));

	if (nullptr != Mover)
	{
		// 아직까지 가야할 경로가 남아있다면
		if (MoverData->CurWaypointIdx < MoverData->WayPointsInfo.Num())
		{
			// 다음 목적지 좌표를 위젯 컴포넌트에 출력
			FVector NextPos = FVector(MoverData->WayPointsInfo[MoverData->CurWaypointIdx].X, MoverData->WayPointsInfo[MoverData->CurWaypointIdx].Y, .0);
			Mover->UpdateWidgetPosInfo(NextPos, EMoverInfoIdx::DestPos);
		
			// 다음 목적지까지의 거리를 계산
			FVector CurPos = Mover->GetActorLocation();
			MoverData->DistanceToDestValue = FVector::Dist2D(CurPos, NextPos);
			SetValueAsObject(OwnerComp, TEXT("MoverData"), MoverData);
		}
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
			
			// 지금 바라보는 방향과 목적지 방향이 같다면 전진
			if (true == IsDestDirSameToCurDir(CurPos, DestPos, MoverData->Dir))
			{
				// Accel 조건
				ChangeState(OwnerComp, EMoverState::Accel);
				return;
			} 
			else // 바라보는 방향이 다르다면 회전
			{
				// 회전 조건
				ChangeState(OwnerComp, EMoverState::Rotate);
				return;
			}
		}
		else // WayPoint 데이터의 Idx 초과 (더이상 이동할 곳이 없다 = 최종목적지)
		{
			// 도착
			ChangeState(OwnerComp, EMoverState::Finish);
			return;
		}
	}
}