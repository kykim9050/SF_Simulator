// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNodeBase_Mover.generated.h"

/**
 * �����̺�� Ʈ������ ����� Mover�� Base �׽�ũ ���
 */
UCLASS()
class UNREALCLIENT_API UBTTaskNodeBase_Mover : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskNodeBase_Mover();

	// SelfActor
	template<typename OwnerType>
	OwnerType* GetSelfActor(UBehaviorTreeComponent& OwnerComp)
	{
		return Cast<OwnerType>(GetSelfActor(OwnerComp));
	}

	AActor* GetSelfActor(UBehaviorTreeComponent& OwnerComp);	

	// Object
	template<typename ObjectType>
	ObjectType* GetValueAsObject(UBehaviorTreeComponent& OwnerComp, FName Name)
	{
		return Cast<ObjectType>(GetValueAsObject(OwnerComp, Name));
	}

	UObject* GetValueAsObject(UBehaviorTreeComponent& OwnerComp, FName Name);
	void SetValueAsObject(UBehaviorTreeComponent& OwnerComp, FName Name, UObject* Value);
};
