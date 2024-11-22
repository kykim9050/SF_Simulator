// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Global/MainGameInstance.h"
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

protected:

private:
	
};
