// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "MoverDataRow.generated.h"


/**
 * Mover�� ������ �� �Һ� ������ ������ �������� ����
 */
USTRUCT(BlueprintType)
struct FMoverDataRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxVelocity = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Accel = 100.0f;

	/// <summary>
	/// DegreeValue
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Rotate = 10.0f;
};

/*
* Mover�� ��� �����Ͱ��� ������Ʈ Ŭ����
*/
UCLASS()
class UMoverData : public UObject
{
	GENERATED_BODY()
public:
	const FMoverDataRow* Data;

	FVector DestPos = FVector();

	TArray<FVector2D> WayPointsInfo = TArray<FVector2D>();
	
	float CurVelocity = 0.0f;
	int CurWaypointIdx = 1;
	EMoverDir Dir = EMoverDir::N;
};