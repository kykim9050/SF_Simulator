// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TestDataComponent.generated.h"

/// <summary>
/// �̵�ü�� ID�� Course ����
/// </summary>
USTRUCT(BlueprintType)
struct FCourseInfo
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Test")
	int MoverID = -1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Test")
	TArray<FVector2D> CourseArray;
};

/// <summary>
/// �׽�Ʈ �����͸� ������ ��ü�� Ŭ���� ������ ����
/// </summary>
USTRUCT(BlueprintType)
struct FTestDataSet
{
	GENERATED_BODY()
public:
	/// <summary>
	/// Key�� �̵�ü�� ID
	/// Value�� �̵�ü �� �̵� ��� ��ǥ ������
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Test", meta = (AllowPrivateAccess = "true"))
	TArray<FCourseInfo> CourseInfo;
};

/// <summary>
/// Test �����͸� Ȱ���� �� �ְ� ���ִ� ������Ʈ
/// </summary>
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCLIENT_API UTestDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTestDataComponent();

	FORCEINLINE FTestDataSet GetTestData() const
	{
		return TestData;
	}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Test", meta = (AllowPrivateAccess = "true"))
	FTestDataSet TestData;
};
