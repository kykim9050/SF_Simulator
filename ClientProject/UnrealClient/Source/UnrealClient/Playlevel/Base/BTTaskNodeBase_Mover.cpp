// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/Base/BTTaskNodeBase_Mover.h"

UBTTaskNodeBase_Mover::UBTTaskNodeBase_Mover()
{
	// Update È°¼ºÈ­
	bNotifyTick = true;
}

AActor* UBTTaskNodeBase_Mover::GetSelfActor(UBehaviorTreeComponent& OwnerComp)
{
	return Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("SelfActor")));
}

UObject* UBTTaskNodeBase_Mover::GetValueAsObject(UBehaviorTreeComponent& OwnerComp, FName Name)
{
	return OwnerComp.GetBlackboardComponent()->GetValueAsObject(Name);
}

void UBTTaskNodeBase_Mover::SetValueAsObject(UBehaviorTreeComponent& OwnerComp, FName Name, UObject* Value)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(Name, Value);
}

void UBTTaskNodeBase_Mover::ChangeState(UBehaviorTreeComponent& _OwnerComp, uint8 _StateChange)
{
	_OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("StateValue"), _StateChange);
	FinishLatentTask(_OwnerComp, EBTNodeResult::Failed);
}

uint8 UBTTaskNodeBase_Mover::GetCurState(UBehaviorTreeComponent& _OwnerComp)
{
	return _OwnerComp.GetBlackboardComponent()->GetValueAsEnum(TEXT("StateValue"));
}

bool UBTTaskNodeBase_Mover::IsDestDirSameToCurDir(FVector _CurPos, FVector _DestPos, EMoverDir _CurDir)
{
	double Dx = _DestPos.Y - _CurPos.Y;
	double Dy = _DestPos.X - _CurPos.X;
	EMoverDir DestDir = EMoverDir::None;

	if (Dx > DirOffset && abs(Dy) <= DirOffset)
	{
		DestDir = EMoverDir::E;
	}
	else if (Dx < (-1) * DirOffset && abs(Dy) <= DirOffset)
	{
		DestDir = EMoverDir::W;
	}
	else if (Dy > DirOffset && abs(Dx) <= DirOffset)
	{
		DestDir = EMoverDir::N;
	}
	else if (Dy < (-1) * DirOffset && abs(Dx) <= DirOffset)
	{
		DestDir = EMoverDir::S;
	}

	if (_CurDir == DestDir)
	{
		return true;
	}
	else
	{
		if (DestDir == EMoverDir::None)
		{
			UE_LOG(LogType, Error, TEXT("if (DestDir == EMoverDir::None). Please Check Dir Value"));
		}
		return false;
	}
}