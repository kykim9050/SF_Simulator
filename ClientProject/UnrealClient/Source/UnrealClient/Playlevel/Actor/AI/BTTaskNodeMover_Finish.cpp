// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/Actor/AI/BTTaskNodeMover_Finish.h"

EBTNodeResult::Type UBTTaskNodeMover_Finish::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	EMoverState StateValue = GetCurState<EMoverState>(OwnerComp);

	// 현재 본인의 상태와 맞지 않다면 Failed
	if (StateValue != EMoverState::Finish)
	{
		return EBTNodeResult::Type::Failed;
	}

	AMover* Mover = GetSelfActor<AMover>(OwnerComp);
	UMainGameInstance* Inst = UGlobalFunctonLibrary::GetMainGameInstance(GetWorld());
	UMoverData* MoverData = GetValueAsObject<UMoverData>(OwnerComp, TEXT("MoverData"));
	
	if (nullptr != MoverData && nullptr != Mover)
	{
		FDateTime CurTime = Inst->GetTimeValue();
		Mover->UpdateWidgetTimeInfo(CurTime, EMoverInfoIdx::EndTime);
		MoverData->FinishTime = CurTime.ToString(TEXT("%H:%M:%S"));
	}

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNodeMover_Finish::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* pNodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, pNodeMemory, DeltaSeconds);

	UMoverData* MoverData = GetValueAsObject<UMoverData>(OwnerComp, TEXT("MoverData"));
	
	if(nullptr != MoverData)
	{
		MoverData->DestroyDelayTime -= DeltaSeconds;

		if (0.0f >= MoverData->DestroyDelayTime)
		{
			AMover* Mover = GetSelfActor<AMover>(OwnerComp);

			if (nullptr != Mover)
			{
				Mover->AllowDestroy();
				FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			}
		}
	}
}