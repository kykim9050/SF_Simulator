// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/SimulatorManager.h"
#include "Playlevel/Test/TestDataComponent.h"
#include "Playlevel/Actor/GridPlatform.h"
#include "Playlevel/Actor/Mover.h"


#include "Playlevel/ClientPlayGameMode.h"

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

	// TestCode NValue Get
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

void ASimulatorManager::SpawnMover(FVector _Pos)
{
	if (nullptr != MoverClass)
	{
		FTransform TransValue = FTransform(FRotator(.0f, .0f, .0f), _Pos, FVector(1.0f, 1.0f, 1.0f));
		AMover* Obj = GetWorld()->SpawnActor<AMover>(MoverClass, TransValue);
		Movers.Add(Obj);
	}
}

void ASimulatorManager::SpawnMoverRepeatedly(float _DeltaTime)
{
	SpawnMoverDeltatime += _DeltaTime;

	if (SpawnMoverDeltatime >= MoverSpawnTimes[MoverSpawnCount])
	{
		AGameModeBase* CurGameMode = GetWorld()->GetAuthGameMode();
		float GridValue = 0.0f;

		if (nullptr != CurGameMode)
		{
			AClientPlayGameMode* CastGameMode = Cast<AClientPlayGameMode>(CurGameMode);

			if (nullptr != CastGameMode)
			{
				GridValue = CastGameMode->GetGridUnitValue();
			}
		}
		// 여기에서 값을 계산해서 위치를 지정해준다.
		FVector2D InitPos = CalMoverInitPos(GridValue, NValue, MoverSpawnCount);

		SpawnMover(FVector(InitPos.X, InitPos.Y, 50.0f));
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

FVector2D ASimulatorManager::CalMoverInitPos(float _GridUintVal, int _N, int _Idx)
{
	float Base = (-1.0f) * (_GridUintVal * static_cast<float>(_N ) / 2.0f) + (_GridUintVal / 2.0f);
	FVector2D RetVal = FVector2D(Base, Base + _GridUintVal * _Idx);
	return RetVal;
}
