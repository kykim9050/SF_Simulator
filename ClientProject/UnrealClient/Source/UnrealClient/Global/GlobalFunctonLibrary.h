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
UCLASS()
class UNREALCLIENT_API UGlobalFunctonLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UMainGameInstance* GetMainGameInstance(const UWorld* WorldContextObject);
	
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

protected:

private:
	
};
