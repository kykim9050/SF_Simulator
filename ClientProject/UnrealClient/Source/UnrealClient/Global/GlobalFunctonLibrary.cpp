// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/GlobalFunctonLibrary.h"
#include "GlobalFunctonLibrary.h"

UMainGameInstance* UGlobalFunctonLibrary::GetMainGameInstance(const UWorld* WorldContextObject)
{
	UMainGameInstance* Inst = WorldContextObject->GetGameInstanceChecked<UMainGameInstance>();

	if (false == Inst->IsValidLowLevel())
	{
		UE_LOG(LogType, Fatal, TEXT("if (false == Inst->IsValidLowLevel())"));
		return nullptr;
	}

	return Inst;
}

void UGlobalFunctonLibrary::LoggingInWidget(const FString& _Log, const UWorld* WorldContextObject)
{
	AClientPlayHUD* CurHUD = GetCurHUD<AClientPlayHUD>(WorldContextObject);

	if (nullptr != CurHUD)
	{
		UClientPlayMainWidget* MainWidget = CurHUD->GetMainWidget();

		if (nullptr != MainWidget)
		{
			MainWidget->AddLogText(_Log);
		}
	}
}
