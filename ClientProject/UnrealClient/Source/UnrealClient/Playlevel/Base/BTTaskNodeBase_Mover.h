// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Playlevel/PlaylevelEnum.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Playlevel/Actor/Mover.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Global/DataTable/MoverDataRow.h"
#include "Global/GlobalFunctonLibrary.h"
#include "BTTaskNodeBase_Mover.generated.h"

/**
 * 비헤이비어 트리에서 사용할 Mover의 Base 테스크 노드
 */
UCLASS()
class UNREALCLIENT_API UBTTaskNodeBase_Mover : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskNodeBase_Mover();

	// SelfActor 관련
	template<typename OwnerType>
	OwnerType* GetSelfActor(UBehaviorTreeComponent& OwnerComp)
	{
		return Cast<OwnerType>(GetSelfActor(OwnerComp));
	}

	AActor* GetSelfActor(UBehaviorTreeComponent& OwnerComp);	


	// Object 관련
	template<typename ObjectType>
	ObjectType* GetValueAsObject(UBehaviorTreeComponent& OwnerComp, FName Name)
	{
		return Cast<ObjectType>(GetValueAsObject(OwnerComp, Name));
	}

	UObject* GetValueAsObject(UBehaviorTreeComponent& OwnerComp, FName Name);

	void SetValueAsObject(UBehaviorTreeComponent& OwnerComp, FName Name, UObject* Value);


	// State 관련
	template<typename EnumType>
	EnumType GetCurState(UBehaviorTreeComponent& _OwnerComp)
	{
		return static_cast<EnumType>(GetCurState(_OwnerComp));
	}

	uint8 GetCurState(UBehaviorTreeComponent& _OwnerComp);

	template<typename EnumType>
	void ChangeState(UBehaviorTreeComponent& _OwnerComp, EnumType _StateChange)
	{
		ChangeState(_OwnerComp, static_cast<uint8>(_StateChange));
	}

	void ChangeState(UBehaviorTreeComponent& _OwnerComp, uint8 _StateChange);

protected:

	bool IsDestDirSameToCurDir(FVector _CurPos, FVector _DestPos, EMoverDir _CurDir);

private:
	double DirOffset = 0.1;

};
