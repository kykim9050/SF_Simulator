// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TestDataComponent.generated.h"

/// <summary>
/// 이동체의 Course 정보
/// </summary>
USTRUCT(BlueprintType)
struct FCourse
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Test")
	TArray<FVector2D> CourseArray;
};

/// <summary>
/// 블루프린트 에디터 상에서 편리하게 테스트 데이터를 수정할 수 있는 클래스
/// </summary>
UCLASS(BlueprintType)
class ATestData : public AActor
{
	GENERATED_BODY()
public:

protected:

private:
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Test", meta = (AllowPrivateAccess = "true"))
	//TMap<int, FMatchPos> MatchingData;

	/// <summary>
	/// Key는 이동체의 ID
	/// Value는 이동체 별 이동 경로 좌표 데이터
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Test", meta = (AllowPrivateAccess = "true"))
	TMap<int, FCourse> CourseInfo;
};

/// <summary>
/// 테스트 데이터를 보유한 객체의 클래스 정보를 포함
/// </summary>
USTRUCT(BlueprintType)
struct FTestDataSet
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Test")
	TSubclassOf<AActor> TestDataClass = nullptr;
};

/// <summary>
/// Test 데이터를 활용할 수 있게 해주는 컴포넌트
/// </summary>
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCLIENT_API UTestDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTestDataComponent();

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
