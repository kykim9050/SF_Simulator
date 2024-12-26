// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/Actor/AI/BTTaskNodeMover_Finish.h"
#include "Networking.h"
#include "Global/Net/ClientPacketManager.h"
#include "Playlevel/ClientPlayGameMode.h"


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
	
	if (nullptr != MoverData && nullptr != Mover && nullptr != Inst)
	{
		FDateTime CurTime = Inst->GetTimeValue();
		Mover->UpdateWidgetTimeInfo(CurTime, EMoverInfoIdx::EndTime);
		FString DateTime = Inst->ConvertToGlobalStandardTime(CurTime);
		MoverData->FinishTime = DateTime;

		// 시작시간, 종료시간 서버측으로 패킷 만들어 보내기 (ID, StartTime 길이, FinishTime길이)
		int32 MyID = Mover->GetID();
		int32 StartTimeLen = MoverData->StartTime.Len();
		int32 FinishTimeLen = MoverData->FinishTime.Len();
		// Payload 구성
		FArrayWriter WriteArray;
		WriteArray << MyID;
		WriteArray << StartTimeLen;
		WriteArray << MoverData->StartTime;
		WriteArray << FinishTimeLen;
		WriteArray << MoverData->FinishTime;
		// 패킷 생성
		TSharedPtr<FBufferArchive> Packet = UClientPacketManager::CreateRequestPacket(EPacketType::InfoSavePacket, WriteArray);
		AClientPlayGameMode* CurGameMode = UGlobalFunctonLibrary::GetClientPlayGameMode(GetWorld());
		if (CurGameMode)
		{
			// 서버로 패킷 송신
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