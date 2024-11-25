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

	/// <summary>
	/// �� ��ġ ������ �Ÿ��� ����ϴ� �Լ� (X, Y�� �ش�)
	/// </summary>
	/// <param name="_MyPos"></param>
	/// <param name="_OtherPos"></param>
	/// <returns></returns>
	double DistanceToDestPos2D(FVector _MyPos, FVector _OtherPos);

	/// <summary>
	/// ���� ��ǥ�� �������� ��ġ ���°� ��� ����ϴ� �Լ�
	/// </summary>
	/// <param name="_CurPos"></param>
	/// <param name="_DestPos"></param>
	/// <returns></returns>
	EMoverDir CheckDir2D(FVector2D _CurPos, FVector2D _DestPos);

	FORCEINLINE double GetGridUnitValue() const
	{
		return GridUnitValue;
	}

	/// <summary>
	/// ���� �ð��� FString���� ��ȯ�ϴ� �Լ�
	/// </summary>
	/// <returns></returns>
	FString GetTimeToString() const;

	/// <summary>
	/// ���� �ð��� FDataTime���·� ��ȯ�ϴ� �Լ�
	/// </summary>
	/// <returns></returns>
	FDateTime GetTimeValue() const;

	/// <summary>
	/// ���� ǥ�� �ð� ������ �Է¹޾Ƽ� Fstring���� ��ȯ�ϴ� ��
	/// </summary>
	/// <returns></returns>
	FString ConvertToGlobalStandardTime(const FDateTime& _DateTime) const;

protected:

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UDataTable* MoverDataTable;

	/// <summary>
	/// GridPlatform�� ���� ���� ��
	/// </summary>
	UPROPERTY()
	double GridUnitValue = 100.0f;
	
	/// <summary>
	/// ���� Ȯ�ν� ����Ǵ� ������ ��
	/// </summary>
	UPROPERTY()
	double DirOffset = 0.1;
};
