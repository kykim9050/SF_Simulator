// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/Actor/AI/BTTaskNodeMover_Accel.h"

EBTNodeResult::Type UBTTaskNodeMover_Accel::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	EMoverState StateValue = GetCurState<EMoverState>(OwnerComp);

	// ���� ������ ���¿� ���� �ʴٸ� Failed
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

	UMoverData* MoverData = GetValueAsObject<UMoverData>(OwnerComp, TEXT("MoverData"));
	
	if (nullptr != Mover)
	{
		FVector CurPos = Mover->GetActorLocation();
		CurPos.Z = .0;
		int CurIdx = MoverData->CurWaypointIdx;
		FVector DestPos = FVector(MoverData->WayPointsInfo[CurIdx].X, MoverData->WayPointsInfo[CurIdx].Y, .0);

		UMainGameInstance* Inst = UGlobalFunctonLibrary::GetMainGameInstance(GetWorld());

		if (1. >= Inst->DistanceToDestPos2D(CurPos, DestPos))
		{
			(MoverData->CurWaypointIdx)++;
			ChangeState(OwnerComp, EMoverState::Idle);
			return;
		}

		FVector Dir = DestPos - CurPos;
		Dir.Normalize();

		// �ӵ� ���� (���ӵ� ���)
		MoverData->CurVelocity = FMath::Min(MoverData->CurVelocity + MoverData->Data->Accel * DeltaSeconds, MoverData->Data->MaxVelocity);

		// ���ӵ� ������ �ӵ�
		Mover->AddActorWorldOffset(DeltaSeconds * Dir * MoverData->CurVelocity);
	}
}
