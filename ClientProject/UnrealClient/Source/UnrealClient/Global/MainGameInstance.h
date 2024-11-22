// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Global/DataTable/MoverDataRow.h"
#include "MainGameInstance.generated.h"

/**
 * ������ ���ص� �����Ǵ� Global�� ���� ������ GameInstance Ŭ����
 */
UCLASS()
class UNREALCLIENT_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="_Name"></param>
	/// <returns></returns>
	const struct FMoverDataRow* GetMoverDataRow(FName _Name);

protected:

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UDataTable* MoverDataTable;
};
