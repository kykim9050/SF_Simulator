// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/Actor/AI/BTTaskNodeMover_Rotate.h"

EBTNodeResult::Type UBTTaskNodeMover_Rotate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	EMoverState StateValue = GetCurState<EMoverState>(OwnerComp);

	// 현재 본인의 상태와 맞지 않다면 Failed
	if (StateValue != EMoverState::Rotate)
	{
		return EBTNodeResult::Type::Failed;
	}

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNodeMover_Rotate::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	UMoverData* MoverData = GetValueAsObject<UMoverData>(OwnerComp, TEXT("MoverData"));
	
	AMover* Mover = GetSelfActor<AMover>(OwnerComp);

	if (nullptr != Mover)
	{
		FVector CurPos = Mover->GetActorLocation();
		CurPos.Z = .0;
		int CurIdx = MoverData->CurWaypointIdx;
		FVector DestPos = FVector(MoverData->WayPointsInfo[CurIdx].X, MoverData->WayPointsInfo[CurIdx].Y, .0);

		UMainGameInstance* Inst = UGlobalFunctonLibrary::GetMainGameInstance(GetWorld());

		// 목적지 방향 계산
		EMoverDir DestDir = CheckDir(CurPos, DestPos);

		// 방향을 체크해서 값이 같아지면 자신의 Dir 값을 바꾼다	
		FVector Forward = Mover->GetActorForwardVector();
		Forward.Normalize();
		FVector NextDir = DestPos - CurPos;
		NextDir.Normalize();
		double DotVal = FVector::DotProduct(Forward, NextDir);
		double ACosAngle = FMath::Acos(DotVal);
		double AngleDegree = FMath::RadiansToDegrees(ACosAngle);
		if (RotateOffsetDegree >= AngleDegree)
		{
			// 방향이 같아졌을 때
			MoverData->Dir = DestDir;
			ChangeState(OwnerComp, EMoverState::Idle);
			return;

		}
		// 같지 않다면 방향이 다른 것
		{
			// 회전할 방향을 정하는 로직 필요
		}

		Mover->AddActorWorldRotation(DeltaSeconds * FQuat(FRotator(.0f, .5f, .0f)));
	}
}