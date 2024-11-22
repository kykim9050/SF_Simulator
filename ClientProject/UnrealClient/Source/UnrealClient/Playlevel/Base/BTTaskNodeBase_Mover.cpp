// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/Base/BTTaskNodeBase_Mover.h"
#include "BehaviorTree/BlackboardComponent.h"

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
