// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Global/DataTable/MoverDataRow.h"
#include "MainGameInstance.generated.h"

/**
 * 레벨이 변해도 유지되는 Global한 값을 보관할 GameInstance 클래스
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

	/// <summary>
	/// 두 위치 사이의 거리를 계산하는 함수 (X, Y만 해당)
	/// </summary>
	/// <param name="_MyPos"></param>
	/// <param name="_OtherPos"></param>
	/// <returns></returns>
	double DistanceToDestPos2D(FVector _MyPos, FVector _OtherPos);

	FORCEINLINE double GetGridUnitValue() const
	{
		return GridUnitValue;
	}

	/// <summary>
	/// 현재 시간을 FString으로 반환하는 함수
	/// </summary>
	/// <returns></returns>
	FString GetTimeToString() const;

	/// <summary>
	/// 현재 시간을 FDataTime형태로 반환하는 함수
	/// </summary>
	/// <returns></returns>
	FDateTime GetTimeValue() const;

protected:

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UDataTable* MoverDataTable;

	/// <summary>
	/// GridPlatform의 길이 단위 값
	/// </summary>
	UPROPERTY()
	double GridUnitValue = 100.0f;
};
