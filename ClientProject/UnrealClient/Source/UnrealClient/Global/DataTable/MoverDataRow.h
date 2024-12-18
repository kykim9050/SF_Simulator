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
	/// <summary>
	/// 고정값 데이터
	/// </summary>
	const FMoverDataRow* Data;

	/// <summary>
	/// 다음 목적지까지 이동해야하는 거리
	/// </summary>
	double DistanceToDestValue = .0;

	/// <summary>
	/// 현재 속력
	/// </summary>
	float CurVelocity = 0.0f;
	
	/// <summary>
	/// 이동해야할 다음 좌표의 인덱스 정보 (WayPointsInfodml 인덱스 정보)
	/// </summary>
	int CurWaypointIdx = 0;

	/// <summary>
	/// Mover 소멸 딜레이 시간 (2초뒤 소멸)
	/// </summary>
	float DestroyDelayTime = 2.0f;

	/// <summary>
	/// 생성 및 임무 종료 시간
	/// </summary>
	FString StartTime = FString(TEXT(""));
	FString FinishTime = FString(TEXT(""));
	
	/// <summary>
	/// Mover의 현재 방향
	/// </summary>
	EMoverDir Dir = EMoverDir::N;

	/// <summary>
	/// 이동해야할 Path (2차원 좌표 배열)
	/// </summary>
	TArray<FVector2D> WayPointsInfo = TArray<FVector2D>();
	
	/// <summary>
	/// 경로 데이터가 저장되었는지에 대한 bool 변수
	/// </summary>
	bool bIsPathRecv = false;
};