// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TestDataComponent.generated.h"


USTRUCT(BlueprintType)
struct FCourse
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Test")
	TArray<FVector2D> CourseArray;
};

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

USTRUCT(BlueprintType)
struct FTestDataSet
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Test")
	TSubclassOf<AActor> TestDataClass = nullptr;
};

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
