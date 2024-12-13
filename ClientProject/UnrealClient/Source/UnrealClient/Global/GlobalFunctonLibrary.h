// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Global/MainGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Playlevel/UI/ClientPlayHUD.h"
#include "Playlevel/UI/ClientPlayMainWidget.h"
#include "GlobalFunctonLibrary.generated.h"

/**
 * 전역 함수를 사용할 수 있는 클래스
 */
class AClientPlayGameMode;
UCLASS()
class UNREALCLIENT_API UGlobalFunctonLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UMainGameInstance* GetMainGameInstance(const UWorld* WorldContextObject);
	
	static AClientPlayGameMode* GetClientPlayGameMode(const UWorld* WorldContextObject);

	/// <summary>
	/// 로그 위젯에 로그 출력 함수
	/// </summary>
	/// <param name="_Log"></param>
	/// <param name="WorldContextObject"></param>
	static void LoggingInWidget(const FString& _Log, const UWorld* WorldContextObject);

	// 원하는 HUD 클래스 포인터형 가져오기
	template<typename Type>
	static Type* GetCurHUD(const UWorld* WorldContextObject)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
		Type* RetHUD = nullptr;

		if (nullptr != PC)
		{
			AHUD* CurHUD = PC->GetHUD();

			if (nullptr != CurHUD)
			{
				RetHUD = Cast<Type>(CurHUD);

				if (nullptr != RetHUD)
				{
					return RetHUD;
				}
			}
		}

		return nullptr;
	}

	template<typename T>
	static void ShuffleTArray(TArray<T>& _Array)
	{
		// 시간을 랜덤의 Seed로 설정
		int32 Seed = FDateTime::Now().GetMillisecond();
		FMath::RandInit(Seed);

		int32 Size = _Array.Num();

		for (int32 i = Size -1; i > 0; --i)
		{
			int32 RandomIdx = FMath::RandRange(0, i);

			if (i != RandomIdx)
			{
				_Array.Swap(i, RandomIdx);
			}
		}
	}

protected:

private:
	
};
