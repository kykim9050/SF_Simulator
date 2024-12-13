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
 * ���� �Լ��� ����� �� �ִ� Ŭ����
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
	/// �α� ������ �α� ��� �Լ�
	/// </summary>
	/// <param name="_Log"></param>
	/// <param name="WorldContextObject"></param>
	static void LoggingInWidget(const FString& _Log, const UWorld* WorldContextObject);

	// ���ϴ� HUD Ŭ���� �������� ��������
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
		int RandValSource = 0;
		uint64_t RandValSourceAddress = reinterpret_cast<uint64_t>(&RandValSource);

		int32 Seed = FMath::FloorToInt(static_cast<float>(RandValSourceAddress));

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
