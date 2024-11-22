// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/Base/BTTaskNodeBase_Mover.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskNodeBase_Mover::UBTTaskNodeBase_Mover()
{
	// Update Ȱ��ȭ
	bNotifyTick = true;
}

AActor* UBTTaskNodeBase_Mover::GetSelfActor(UBehaviorTreeComponent& OwnerComp)
{
	return Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("SelfActor")));
}
