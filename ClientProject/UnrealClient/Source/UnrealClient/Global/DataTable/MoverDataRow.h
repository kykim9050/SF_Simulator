// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Playlevel/PlaylevelEnum.h"
#include "MoverDataRow.generated.h"


/**
 * Mover의 데이터 중 불변 값으로 지정될 변수들의 모음
 */
USTRUCT(BlueprintType)
struct FMoverDataRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	/// <summary>
	/// 언리얼의 기본 길이 단위는 cm
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
* Mover의 모든 데이터관련 오브젝트 클래스
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