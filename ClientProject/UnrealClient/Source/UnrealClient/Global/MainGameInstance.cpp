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

double UMainGameInstance::DistanceToDestPos2D(FVector _MyPos, FVector _OtherPos)
{
	double Dist = sqrt((_MyPos.X - _OtherPos.X) * (_MyPos.X - _OtherPos.X) + (_MyPos.Y - _OtherPos.Y) * (_MyPos.Y - _OtherPos.Y));
	return Dist;
}

EMoverDir UMainGameInstance::CheckDir2D(FVector2D _CurPos, FVector2D _DestPos)
{
	EMoverDir Result = EMoverDir::None;

	double Dx = _DestPos.Y - _CurPos.Y;
	double Dy = _DestPos.X - _CurPos.X;

	if (Dx > DirOffset && abs(Dy) <= DirOffset)
	{
		Result = EMoverDir::E;
	}
	else if (Dx < (-1) * DirOffset && abs(Dy) <= DirOffset)
	{
		Result = EMoverDir::W;
	}
	else if (Dy > DirOffset && abs(Dx) <= DirOffset)
	{
		Result = EMoverDir::N;
	}
	else if (Dy < (-1) * DirOffset && abs(Dx) <= DirOffset)
	{
		Result = EMoverDir::S;
	}

	return Result;
}

FString UMainGameInstance::GetTimeToString() const
{
	FDateTime CurrentTime = FDateTime::Now();
	return CurrentTime.ToString(TEXT("%H:%M:%S"));
}

FDateTime UMainGameInstance::GetTimeValue() const
{
	FDateTime CurrentTime = FDateTime::Now();
	return CurrentTime;
}

FString UMainGameInstance::ConvertToGlobalStandardTime(const FDateTime& _DateTime) const
{
	FString DateStr = FString(_DateTime.ToString(TEXT("%Y-%m-%d"))) + FString("T") + FString(_DateTime.ToString(TEXT("%H:%M:%S")));
	return DateStr;
}