// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/Actor/AI/BTTaskNodeMover_Idle.h"

EBTNodeResult::Type UBTTaskNodeMover_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	EMoverState StateValue = GetCurState<EMoverState>(OwnerComp);

	// ���� ������ ���¿� ���� �ʴٸ� Failed
	if (StateValue != EMoverState::Idle)
	{
		return EBTNodeResult::Type::Failed;
	}


	AMover* Mover = GetSelfActor<AMover>(OwnerComp);
	UMoverData* MoverData = GetValueAsObject<UMoverData>(OwnerComp, TEXT("MoverData"));

	if (nullptr != Mover)
	{
		// �������� ������ ��ΰ� �����ִٸ�
		if (MoverData->CurWaypointIdx < MoverData->WayPointsInfo.Num())
		{
			// ���� ������ ��ǥ�� ���� ������Ʈ�� ���
			FVector NextPos = FVector(MoverData->WayPointsInfo[MoverData->CurWaypointIdx].X, MoverData->WayPointsInfo[MoverData->CurWaypointIdx].Y, .0);
			Mover->UpdateWidgetPosInfo(NextPos, EMoverInfoIdx::DestPos);
		
			// ���� ������������ �Ÿ��� ���
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

		// �̵��ؾ��� ��ǥ Idx�� ���� ������ ��
		if (CurIdx < MoverData->WayPointsInfo.Num())
		{
			FVector DestPos = FVector(MoverData->WayPointsInfo[CurIdx].X, MoverData->WayPointsInfo[CurIdx].Y, .0);

			UMainGameInstance* Inst = UGlobalFunctonLibrary::GetMainGameInstance(GetWorld());
			
			// ���� �ٶ󺸴� ����� ������ ������ ���ٸ� ����
			if (true == IsDestDirSameToCurDir(CurPos, DestPos, MoverData->Dir))
			{
				// Accel ����
				ChangeState(OwnerComp, EMoverState::Accel);
				return;
			} 
			else // �ٶ󺸴� ������ �ٸ��ٸ� ȸ��
			{
				// ȸ�� ����
				ChangeState(OwnerComp, EMoverState::Rotate);
				return;
			}
		}
		else // WayPoint �������� Idx �ʰ� (���̻� �̵��� ���� ���� = ����������)
		{
			// ����
			ChangeState(OwnerComp, EMoverState::Finish);
			return;
		}
	}
}