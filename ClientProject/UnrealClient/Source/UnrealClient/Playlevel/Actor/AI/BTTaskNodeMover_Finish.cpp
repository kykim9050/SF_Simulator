// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/Actor/AI/BTTaskNodeMover_Finish.h"
#include "Networking.h"
#include "Global/Net/ClientPacketManager.h"
#include "Playlevel/ClientPlayGameMode.h"


EBTNodeResult::Type UBTTaskNodeMover_Finish::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	EMoverState StateValue = GetCurState<EMoverState>(OwnerComp);

	// ���� ������ ���¿� ���� �ʴٸ� Failed
	if (StateValue != EMoverState::Finish)
	{
		return EBTNodeResult::Type::Failed;
	}

	AMover* Mover = GetSelfActor<AMover>(OwnerComp);
	UMainGameInstance* Inst = UGlobalFunctonLibrary::GetMainGameInstance(GetWorld());
	UMoverData* MoverData = GetValueAsObject<UMoverData>(OwnerComp, TEXT("MoverData"));
	
	if (nullptr != MoverData && nullptr != Mover && nullptr != Inst)
	{
		FDateTime CurTime = Inst->GetTimeValue();
		Mover->UpdateWidgetTimeInfo(CurTime, EMoverInfoIdx::EndTime);
		FString DateTime = Inst->ConvertToGlobalStandardTime(CurTime);
		MoverData->FinishTime = DateTime;

		// ���۽ð�, ����ð� ���������� ��Ŷ ����� ������ (ID, StartTime ����, FinishTime����)
		int32 MyID = Mover->GetID();
		int32 StartTimeLen = MoverData->StartTime.Len();
		int32 FinishTimeLen = MoverData->FinishTime.Len();
		// Payload ����
		FArrayWriter WriteArray;
		WriteArray << MyID;
		WriteArray << StartTimeLen;
		WriteArray << MoverData->StartTime;
		WriteArray << FinishTimeLen;
		WriteArray << MoverData->FinishTime;
		// ��Ŷ ����
		TSharedPtr<FBufferArchive> Packet = UClientPacketManager::CreateRequestPacket(EPacketType::InfoSavePacket, WriteArray);
		AClientPlayGameMode* CurGameMode = UGlobalFunctonLibrary::GetClientPlayGameMode(GetWorld());
		if (CurGameMode)
		{
			// ������ ��Ŷ �۽�
			CurGameMode->GetTCPClient()->SendData(*(Packet.Get()));
		}
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