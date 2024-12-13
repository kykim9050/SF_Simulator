// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimulatorManager.generated.h"

/*
* Simulation을 위해 GridFloor와 Mover를 관리 및 제어하는 클래스
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
	/// N값을 입력 받아 수행하는 SpawnGridPlatform
	/// </summary>
	/// <param name="_Pos"></param>
	void GridInit(int32 _N, FVector _Pos = FVector(.0f, .0f, .0f));

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetIsMoversSpawnable()
	{
		bIsMoversSpawnable = true;
	}

	/// <summary>
	/// 본인이 소유한 모든 액터들을 반환했는지에 대한 유무를 반환
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
	/// 경로를 꺾이는 기점으로 구분해서 경로 데이터를 압축하는 함수
	/// 실제 좌표로의 변환도 함께 이루어진다.
	/// </summary>
	TArray<FVector2D> PathModify(TArray<FVector2D>& _Course);
	
	/// <summary>
	/// 액터를 삭제하는 함수
	/// 안전하게 본인이 가지고 있는 액터를 반환하기 위해서 Tick에서 지속적으로 확인한다.
	/// </summary>
	void ReleaseActor();

	/// <summary>
	/// Mover를 Spawn하는 함수
	/// _Pos : World에서 생성하고자 하는 위치 (중심)
	/// </summary>
	/// <param name="_Pos"></param>
	void SpawnMover(FVector _Pos = FVector(.0f, .0f, .0f), int _MoverID = 0);

	/// <summary>
	/// DestSign을 Spawn하는 함수
	/// _Pos : World에서 생성하고자 하는 위치 (중심)
	/// </summary>
	/// <param name="_Pos"></param>
	void SpawnDestSign(FVector _Pos = FVector(.0f, .0f, .0f), int _MoverID = 0);

	/// <summary>
	/// Mover Spawn을 여러번 수행하는 함수
	/// </summary>
	/// <param name="_DeltaTime"></param>
	void SpawnMoverRepeatedly(float _DeltaTime);

	/// <summary>
	/// N의 크기에 맞게 MoverSpawnTimes의 배열 요소와 크기를 조정하는 함수
	/// </summary>
	void InitMoverSpawnTimes(int _N);

	/// <summary>
	/// Mover의 생성 초기 위치를 지정해주는 함수
	/// </summary>
	FVector2D CalMoverInitPos(double _GridUintVal, int _N, int _Idx);

	/// <summary>
	/// 일반 서버에서 받은 좌표를 실제 Unreal의 좌표로 바꾸어주는 함수
	/// </summary>
	/// <param name="_Pos"></param>
	/// <param name="_GridUnitVal"></param>
	/// <param name="_N"></param>
	FVector2D ConvertToRealPos(FVector2D _Pos, double _GridUnitVal, int _N);

	/// <summary>
	///	지정된 ID에 해당하는 Mover에게 이동할 위치를 전달하는 로직
	/// </summary>
	/// <param name="_MoverID"></param>
	/// <param name="_TargetPos"></param>
	void SendTargetPosInfoToMover(int _MoverID, FVector _TargetPos);

	FORCEINLINE void SetNValue(int32 _N)
	{
		NValue = _N;
	}

	/// <summary>
	/// 이동체와 목적지의 위치를 랜덤으로 초기화 하는 함수
	/// </summary>
	/// <param name="_N"></param>
	void MoverAndDestPosInit(int32 _N);

private:

	/// <summary>
	/// GridPlatform을 Spawn하는 함수
	/// _Pos : World에서 생성하고자 하는 위치 (중심)
	/// </summary>
	void SpawnGridPlatform(FVector _Pos = FVector(.0f, .0f, .0f));
	
	// Test용 데이터 (로봇 아이디, 경로 정보 전달 용)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Test Prop", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTestDataComponent> TestDataComponent = nullptr;

	/// <summary>
	/// 블루프린트 상에서 생성할 GridPlatform 객체를 지정, 클래스 정보 저장
	/// </summary>
	UPROPERTY(Editanywhere, Category = "Insert Parameter", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> GridPlatformClass = nullptr;

	/// <summary>
	/// GridPlatform의 포인터를 소유
	/// </summary>
	TObjectPtr<AGridPlatform> GridPlatform = nullptr;

	/// <summary>
	/// 블루프린트 상에서 생성할 Mover 객체를 지정, 클래스 정보 저장
	/// </summary>
	UPROPERTY(Editanywhere, Category = "Insert Parameter", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ACharacter> MoverClass = nullptr;

	/// <summary>
	/// 생성될 Mover 객체들 정보 소유
	/// </summary>
	TMap<int, TObjectPtr<AMover>> Movers = TMap<int, TObjectPtr<AMover>>();

	/// <summary>
	/// 블루프린트 상에서 생성할 DestSign 객체를 지정, 클래스 정보 저장
	/// </summary>
	UPROPERTY(Editanywhere, Category = "Insert Parameter", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> DestSignClass = nullptr;

	/// <summary>
	/// 생성된 DestSigns 객체들 정보 소유
	/// </summary>
	TMap<int, TObjectPtr<ADestSign>> DestSigns = TMap<int, TObjectPtr<ADestSign>>();

	/// <summary>
	/// Mover별 Spawn 시간 보유
	/// </summary>
	TArray<float> MoverSpawnTimes = TArray<float>({ 0.0f, 1.0f, 2.0f });

	/// <summary>
	/// 서버에서 받아올 N값
	/// </summary>
	int32 NValue = 1;

	/// <summary>
	/// Mover를 연속적으로 출력하기 위한 시그널 변수
	/// </summary>
	bool bIsMoversSpawnable = false;

	/// <summary>
	/// Mover를 연속으로 Spawn할때 활용할 시간 데이터
	/// </summary>
	float SpawnMoverDeltatime = 0.0f;

	/// <summary>
	/// Mover를 연속으로 몇 개 카운트 했는지 연산을 적용할 변수
	/// </summary>
	int MoverSpawnCount = 0;

	/// <summary>
	/// 릴리즈한 Mover & DestSign 세트 수
	/// </summary>
	int DestroyCount = 0;

	/// <summary>
	/// Mover와 DestSign의 초기 위치를 위한 배열 소스
	/// </summary>
	TArray<int> MoversInitPosSource = TArray<int>();
	TArray<int> DestSignsInitPosSource = TArray<int>();
};
