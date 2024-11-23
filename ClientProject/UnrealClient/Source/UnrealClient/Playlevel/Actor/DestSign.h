// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global/Base/ObjectID.h"
#include "DestSign.generated.h"

/*
* ������ ������ ������ ����
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
	/// ID�� �Է��ϴ� ���ÿ� �ڽ��� ������Ʈ ���̵� �ʱ�ȭ �Ѵ�.
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
	/// ID�� ��Ÿ�� �� �ִ� ���� ������Ʈ	
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Property", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> IDComponent = nullptr;
	
	/// <summary>
	/// ��Ī�� ID���� ���� Ŭ���� ����
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Property", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> IDComponentWidgetClass = nullptr;
};
