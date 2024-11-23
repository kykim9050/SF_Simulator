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

float UBTTaskNodeBase_Mover::DistanceToDestPos(FVector _CurPos, FVector _DestPos)
{
	return 0.0f;
}