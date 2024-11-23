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

	UMoverData* MoverData = GetValueAsObject<UMoverData>(OwnerComp, TEXT("MoverData"));
	
	AMover* Mover = GetSelfActor<AMover>(OwnerComp);

	if (nullptr != Mover)
	{
		FVector CurPos = Mover->GetActorLocation();
		CurPos.Z = .0;
		int CurIdx = MoverData->CurWaypointIdx;
		FVector DestPos = FVector(MoverData->WayPointsInfo[CurIdx].X, MoverData->WayPointsInfo[CurIdx].Y, .0);

		UMainGameInstance* Inst = UGlobalFunctonLibrary::GetMainGameInstance(GetWorld());

		// ������ ���� ���
		EMoverDir DestDir = CheckDir(CurPos, DestPos);

		// ������ üũ�ؼ� ���� �������� �ڽ��� Dir ���� �ٲ۴�	
		FVector Forward = Mover->GetActorForwardVector();
		Forward.Normalize();
		FVector NextDir = DestPos - CurPos;
		NextDir.Normalize();
		double DotVal = FVector::DotProduct(Forward, NextDir);
		double ACosAngle = FMath::Acos(DotVal);
		double AngleDegree = FMath::RadiansToDegrees(ACosAngle);

		double rotateVal = .5;

		if (RotateOffsetDegree >= AngleDegree)
		{
			// ������ �������� ��
			MoverData->Dir = DestDir;
			ChangeState(OwnerComp, EMoverState::Idle);
			return;

		}
		// ���� �ʴٸ� ������ �ٸ� ��
		{
			// ������ Ȱ���ؼ� ȸ���� ���� �����ϱ�
			FVector CrossVal = FVector::CrossProduct(Forward, NextDir);
			
			if (CrossVal.Z > 0.)
			{
				rotateVal = 0.5;
			}
			else if (CrossVal.Z <= 0.)
			{
				rotateVal = -0.5;
			}
		}

		Mover->AddActorWorldRotation(DeltaSeconds * FQuat(FRotator(.0, rotateVal, .0)));
	}
}