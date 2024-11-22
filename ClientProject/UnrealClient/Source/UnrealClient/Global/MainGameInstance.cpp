// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/MainGameInstance.h"
#include "MainGameInstance.h"

const FMoverDataRow* UMainGameInstance::GetMoverDataRow(FName _Name)
{
	if (nullptr == MoverDataTable)
	{
		UE_LOG(LogType, Fatal, TEXT("if (nullptr == MoverDataTable)"));
	}

	FMoverDataRow* MoverData = MoverDataTable->FindRow<FMoverDataRow>(_Name, nullptr);

	if (nullptr == MoverData)
	{
		UE_LOG(LogType, Error, TEXT("%s Name Data Is Nullptr"), *_Name.ToString());
		return nullptr;
	}

	return MoverData;
}
