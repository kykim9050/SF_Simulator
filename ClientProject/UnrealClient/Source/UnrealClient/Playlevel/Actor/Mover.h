// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Global/Base/ObjectID.h"
#include "Mover.generated.h"

/*
* �̵�ü Ŭ����
*/
class UStaticMeshComponent;
class UArrowComponent;
class ASimulatorManager;
class ABaseMoverAIController;
class AAIController;
class UWidgetComponent;
class UMoverData;
struct FMoverDataRow;
UCLASS()
class UNREALCLIENT_API AMover : public ACharacter, public ObjectID
{
	GENERATED_BODY()

	friend ASimulatorManager;

public:
	// Sets default values for this pawn's properties
	AMover();

	FORCEINLINE FVector GetTargetPos() const
	{
		return TargetPos;
	}

	FORCEINLINE void SetTargetPos(FVector _TargetPos)
	{
		TargetPos = _TargetPos;
	}

	FORCEINLINE ABaseMoverAIController* GetAIController() const
	{
		return AIController;
	}

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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	/// <summary>
	/// Mover�� ���� �Žÿ� ������Ʈ
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> MoverMeshComponent = nullptr;

	/// <summary>
	/// ID�� ��Ÿ�� �� �ִ� ���� ������Ʈ
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Property", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> IDComponent = nullptr;

	UPROPERTY()
	FVector TargetPos = FVector();

	/// <summary>
	/// ��Ī�� ID���� ���� Ŭ���� ����
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Property", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> IDComponentWidgetClass = nullptr;

	/// <summary>
	/// ��Ī�� AICOntroller Ŭ���� ����
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Property", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AAIController> MatchingAIControllerClass = nullptr;

	/// <summary>
	/// Mover�� ������ AIController ������
	/// </summary>
	UPROPERTY()
	TObjectPtr<ABaseMoverAIController> AIController = nullptr;

	/// <summary>
	/// Mover�� ��� �����͸� ����
	/// </summary>
	UPROPERTY()
	UMoverData* SettingData;

	/// <summary>
	/// ������ ���̺� �� � �̸��� ���̺��� ������ ������ �ĺ���
	/// </summary>
	UPROPERTY(EditAnywhere, Category = "Setting Data Name", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName StatusName;

	/// <summary>
	/// ���� ������ ���鿡 ���� ������
	/// </summary>
	const FMoverDataRow* BaseData;
};
