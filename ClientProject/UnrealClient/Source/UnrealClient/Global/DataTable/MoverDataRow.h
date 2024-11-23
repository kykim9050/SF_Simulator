// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Playlevel/PlaylevelEnum.h"
#include "MoverDataRow.generated.h"


/**
 * Mover�� ������ �� �Һ� ������ ������ �������� ����
 */
USTRUCT(BlueprintType)
struct FMoverDataRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	/// <summary>
	/// �𸮾��� �⺻ ���� ������ cm
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double MaxVelocity = 100.; // = 1m

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Accel = 10.;	// = 0.1m

	/// <summary>
	/// DegreeValue
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Rotate = 10.;	// degree
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