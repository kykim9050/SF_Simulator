// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/SimulatorManager.h"
#include "Playlevel/Test/TestDataComponent.h"
#include "Playlevel/Actor/GridPlatform.h"
#include "Playlevel/Actor/Mover.h"
#include "Global/GlobalFunctonLibrary.h"

// Sets default values
ASimulatorManager::ASimulatorManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TestDataComponent = CreateDefaultSubobject<UTestDataComponent>(TEXT("TestDataComponent"));
}

// Called when the game starts or when spawned
void ASimulatorManager::BeginPlay()
{
	Super::BeginPlay();

	// 테스트 코드 NValue Get
	NValue = TestDataComponent->GetTestData().CourseInfo.Num();
	InitMoverSpawnTimes(NValue);
}

// Called every frame
void ASimulatorManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (true == bIsMoversSpawnable)
	{
		SpawnMoverRepeatedly(DeltaTime);
	}
}

void ASimulatorManager::SpawnGridPlatform(FVector _Pos)
{
	if (nullptr != GridPlatformClass)
	{
		FTransform TransValue = FTransform(FRotator(.0f, .0f, .0f), _Pos, FVector(NValue * 1.0f, NValue * 1.0f, 1.0f));
		GridPlatform = GetWorld()->SpawnActor<AGridPlatform>(GridPlatformClass, TransValue);
	}
}

void ASimulatorManager::SpawnMover(FVector _Pos, int _MoverID)
{
	if (nullptr != MoverClass)
	{
		FTransform TransValue = FTransform(FRotator(.0f, .0f, .0f), _Pos, FVector(1.0f, 1.0f, 1.0f));
		AMover* Obj = GetWorld()->SpawnActor<AMover>(MoverClass, TransValue);
		// Mover에게 ID를 부여한다.
		Obj->SetID(_MoverID);

		// 초기 생성시 목표 좌표를 전달 (Test용)
		int Size = TestDataComponent->GetTestData().CourseInfo[MoverSpawnCount].CourseArray.Num();
		

		UMainGameInstance* Inst = UGlobalFunctonLibrary::GetMainGameInstance(GetWorld());

		TArray<FVector2D> ConvertPathInfo = TArray<FVector2D>();

		for (int i = 0; i < Size; i++)
		{
			FVector2D Vector = TestDataComponent->GetTestData().CourseInfo[MoverSpawnCount].CourseArray[i];
			FVector2D TransVec = ConvertToRealPos(Vector, Inst->GetGridUnitValue(), NValue);
			ConvertPathInfo.Add(TransVec);
		}

		Obj->SetWayPoints(ConvertPathInfo);
		Movers.Add(_MoverID) = Obj;
	}
}

void ASimulatorManager::SpawnMoverRepeatedly(float _DeltaTime)
{
	SpawnMoverDeltatime += _DeltaTime;

	if (SpawnMoverDeltatime >= MoverSpawnTimes[MoverSpawnCount])
	{
		UMainGameInstance* Inst = UGlobalFunctonLibrary::GetMainGameInstance(GetWorld());

		// 값을 계산해서 Mover 초기 위치를 지정해준다.
		FVector2D InitPos = CalMoverInitPos(Inst->GetGridUnitValue(), NValue, MoverSpawnCount);

		int RobotID = TestDataComponent->GetTestData().CourseInfo[MoverSpawnCount].MoverID;
		// 현재 ID는 TestData에서 가져오고 있다.
		SpawnMover(FVector(InitPos.X, InitPos.Y, 100.0f), RobotID);
		++MoverSpawnCount;

		if (NValue <= MoverSpawnCount)
		{
			bIsMoversSpawnable = false;
		}
	}
}

void ASimulatorManager::InitMoverSpawnTimes(int _N)
{
	for (int i = 3; i < _N; ++i)
	{
		MoverSpawnTimes.Add(MoverSpawnTimes[i - 1] + MoverSpawnTimes[i - 2]);
	}
}

FVector2D ASimulatorManager::CalMoverInitPos(double _GridUintVal, int _N, int _Idx)
{
	double Base = (-1.0f) * (_GridUintVal * static_cast<double>(_N ) / 2.0f) + (_GridUintVal / 2.0f);
	FVector2D RetVal = FVector2D(Base, Base + _GridUintVal * _Idx);
 	return RetVal;
}

FVector2D ASimulatorManager::ConvertToRealPos(FVector2D _Pos, double _GridUnitVal, int _N)
{
	double Base = static_cast<double>(_N - 1) * (_GridUnitVal / 2.0) * (-1.0);
	FVector2D Result = FVector2D();

	// unreal 기준 좌표계 반영 필요
	Result.Y = Base + _Pos.Y * _GridUnitVal;
	Result.X = Base + ((_N - 1 - _Pos.X) * _GridUnitVal);

	return Result;
}

void ASimulatorManager::SendTargetPosInfoToMover(int _MoverID, FVector _TargetPos)
{
	// 이동해야 할 로직에서 꺾는 부분을 기준으로 한번에 이동할 위치를 계산

	// 자료구조에 _MoverID와 매칭되는 데이터가 존재할 때만 실행
	if (nullptr != Movers.FindChecked(_MoverID))
	{
		Movers.Find(_MoverID)->Get()->SetTargetPos(_TargetPos);
	}
}
