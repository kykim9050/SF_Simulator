// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimulatorManager.generated.h"

/*
* Simulation�� ���� GridFloor�� Mover�� ���� �� �����ϴ� Ŭ����
*/
class UTestDataComponent;
class AGridPlatform;
class AMover;
class ACharacter;
class ADestSign;
UCLASS()
class UNREALCLIENT_API ASimulatorManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimulatorManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	/// <summary>
	/// N���� �Է� �޾� �����ϴ� SpawnGridPlatform
	/// </summary>
	/// <param name="_Pos"></param>
	void GridInit(int32 _N, FVector _Pos = FVector(.0f, .0f, .0f));

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetIsMoversSpawnable()
	{
		bIsMoversSpawnable = true;
	}

	/// <summary>
	/// ������ ������ ��� ���͵��� ��ȯ�ߴ����� ���� ������ ��ȯ
	/// </summary>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable)
	bool IsDestroyAllActor()
	{
		return NValue == DestroyCount;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/// <summary>
	/// ��θ� ���̴� �������� �����ؼ� ��� �����͸� �����ϴ� �Լ�
	/// ���� ��ǥ���� ��ȯ�� �Բ� �̷������.
	/// </summary>
	TArray<FVector2D> PathModify(TArray<FVector2D>& _Course);
	
	/// <summary>
	/// ���͸� �����ϴ� �Լ�
	/// �����ϰ� ������ ������ �ִ� ���͸� ��ȯ�ϱ� ���ؼ� Tick���� ���������� Ȯ���Ѵ�.
	/// </summary>
	void ReleaseActor();

	/// <summary>
	/// Mover�� Spawn�ϴ� �Լ�
	/// _Pos : World���� �����ϰ��� �ϴ� ��ġ (�߽�)
	/// </summary>
	/// <param name="_Pos"></param>
	void SpawnMover(FVector _Pos = FVector(.0f, .0f, .0f), int _MoverID = 0);

	/// <summary>
	/// DestSign�� Spawn�ϴ� �Լ�
	/// _Pos : World���� �����ϰ��� �ϴ� ��ġ (�߽�)
	/// </summary>
	/// <param name="_Pos"></param>
	void SpawnDestSign(FVector _Pos = FVector(.0f, .0f, .0f), int _MoverID = 0);

	/// <summary>
	/// Mover Spawn�� ������ �����ϴ� �Լ�
	/// </summary>
	/// <param name="_DeltaTime"></param>
	void SpawnMoverRepeatedly(float _DeltaTime);

	/// <summary>
	/// N�� ũ�⿡ �°� MoverSpawnTimes�� �迭 ��ҿ� ũ�⸦ �����ϴ� �Լ�
	/// </summary>
	void InitMoverSpawnTimes(int _N);

	/// <summary>
	/// Mover�� ���� �ʱ� ��ġ�� �������ִ� �Լ�
	/// </summary>
	FVector2D CalMoverInitPos(double _GridUintVal, int _N, int _Idx);

	/// <summary>
	/// �Ϲ� �������� ���� ��ǥ�� ���� Unreal�� ��ǥ�� �ٲپ��ִ� �Լ�
	/// </summary>
	/// <param name="_Pos"></param>
	/// <param name="_GridUnitVal"></param>
	/// <param name="_N"></param>
	FVector2D ConvertToRealPos(FVector2D _Pos, double _GridUnitVal, int _N);

	/// <summary>
	///	������ ID�� �ش��ϴ� Mover���� �̵��� ��ġ�� �����ϴ� ����
	/// </summary>
	/// <param name="_MoverID"></param>
	/// <param name="_TargetPos"></param>
	void SendTargetPosInfoToMover(int _MoverID, FVector _TargetPos);

	FORCEINLINE void SetNValue(int32 _N)
	{
		NValue = _N;
	}

	/// <summary>
	/// �̵�ü�� �������� ��ġ�� �������� �ʱ�ȭ �ϴ� �Լ�
	/// </summary>
	/// <param name="_N"></param>
	void MoverAndDestPosInit(int32 _N);

private:

	/// <summary>
	/// GridPlatform�� Spawn�ϴ� �Լ�
	/// _Pos : World���� �����ϰ��� �ϴ� ��ġ (�߽�)
	/// </summary>
	void SpawnGridPlatform(FVector _Pos = FVector(.0f, .0f, .0f));
	
	// Test�� ������ (�κ� ���̵�, ��� ���� ���� ��)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Test Prop", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTestDataComponent> TestDataComponent = nullptr;

	/// <summary>
	/// �������Ʈ �󿡼� ������ GridPlatform ��ü�� ����, Ŭ���� ���� ����
	/// </summary>
	UPROPERTY(Editanywhere, Category = "Insert Parameter", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> GridPlatformClass = nullptr;

	/// <summary>
	/// GridPlatform�� �����͸� ����
	/// </summary>
	TObjectPtr<AGridPlatform> GridPlatform = nullptr;

	/// <summary>
	/// �������Ʈ �󿡼� ������ Mover ��ü�� ����, Ŭ���� ���� ����
	/// </summary>
	UPROPERTY(Editanywhere, Category = "Insert Parameter", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ACharacter> MoverClass = nullptr;

	/// <summary>
	/// ������ Mover ��ü�� ���� ����
	/// </summary>
	TMap<int, TObjectPtr<AMover>> Movers = TMap<int, TObjectPtr<AMover>>();

	/// <summary>
	/// �������Ʈ �󿡼� ������ DestSign ��ü�� ����, Ŭ���� ���� ����
	/// </summary>
	UPROPERTY(Editanywhere, Category = "Insert Parameter", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> DestSignClass = nullptr;

	/// <summary>
	/// ������ DestSigns ��ü�� ���� ����
	/// </summary>
	TMap<int, TObjectPtr<ADestSign>> DestSigns = TMap<int, TObjectPtr<ADestSign>>();

	/// <summary>
	/// Mover�� Spawn �ð� ����
	/// </summary>
	TArray<float> MoverSpawnTimes = TArray<float>({ 0.0f, 1.0f, 2.0f });

	/// <summary>
	/// �������� �޾ƿ� N��
	/// </summary>
	int32 NValue = 1;

	/// <summary>
	/// Mover�� ���������� ����ϱ� ���� �ñ׳� ����
	/// </summary>
	bool bIsMoversSpawnable = false;

	/// <summary>
	/// Mover�� �������� Spawn�Ҷ� Ȱ���� �ð� ������
	/// </summary>
	float SpawnMoverDeltatime = 0.0f;

	/// <summary>
	/// Mover�� �������� �� �� ī��Ʈ �ߴ��� ������ ������ ����
	/// </summary>
	int MoverSpawnCount = 0;

	/// <summary>
	/// �������� Mover & DestSign ��Ʈ ��
	/// </summary>
	int DestroyCount = 0;

	/// <summary>
	/// Mover�� DestSign�� �ʱ� ��ġ�� ���� �迭 �ҽ�
	/// </summary>
	TArray<int> MoversInitPosSource = TArray<int>();
	TArray<int> DestSignsInitPosSource = TArray<int>();
};
