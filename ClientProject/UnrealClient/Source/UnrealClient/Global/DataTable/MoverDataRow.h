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
	/// <summary>
	/// ������ ������
	/// </summary>
	const FMoverDataRow* Data;

	/// <summary>
	/// ���� ���������� �̵��ؾ��ϴ� �Ÿ�
	/// </summary>
	double DistanceToDestValue = .0;

	/// <summary>
	/// ���� �ӷ�
	/// </summary>
	float CurVelocity = 0.0f;
	
	/// <summary>
	/// �̵��ؾ��� ���� ��ǥ�� �ε��� ���� (WayPointsInfodml �ε��� ����)
	/// </summary>
	int CurWaypointIdx = 0;

	/// <summary>
	/// Mover �Ҹ� ������ �ð� (2�ʵ� �Ҹ�)
	/// </summary>
	float DestroyDelayTime = 2.0f;

	/// <summary>
	/// ���� �� �ӹ� ���� �ð�
	/// </summary>
	FString StartTime = FString(TEXT(""));
	FString FinishTime = FString(TEXT(""));
	
	/// <summary>
	/// Mover�� ���� ����
	/// </summary>
	EMoverDir Dir = EMoverDir::N;

	/// <summary>
	/// �̵��ؾ��� Path (2���� ��ǥ �迭)
	/// </summary>
	TArray<FVector2D> WayPointsInfo = TArray<FVector2D>();
	
	/// <summary>
	/// ��� �����Ͱ� ����Ǿ������� ���� bool ����
	/// </summary>
	bool bIsPathRecv = false;
};