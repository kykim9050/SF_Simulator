// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global/Base/ObjectID.h"
#include "DestSign.generated.h"

/*
* 도착지 정보를 보여줄 액터
*/
class UWidgetComponent;
UCLASS()
class UNREALCLIENT_API ADestSign : public AActor, public ObjectID
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestSign();

	/// <summary>
	/// ID를 입력하는 동시에 자신의 컴포넌트 아이디도 초기화 한다.
	/// </summary>
	/// <param name="_ID"></param>
	void SetID(int _ID) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/// <summary>
	/// ID를 나타낼 수 있는 위젯 컴포넌트	
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Property", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> IDComponent = nullptr;
	
	/// <summary>
	/// 매칭할 ID위젯 관련 클래스 정보
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Property", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> IDComponentWidgetClass = nullptr;
};
