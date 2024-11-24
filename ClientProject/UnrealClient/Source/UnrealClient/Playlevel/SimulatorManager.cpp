// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/SimulatorManager.h"
#include "Playlevel/Test/TestDataComponent.h"
#include "Playlevel/Actor/GridPlatform.h"
#include "Playlevel/Actor/Mover.h"
#include "Global/GlobalFunctonLibrary.h"
#include "Playlevel/Actor/DestSign.h"

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

	// �׽�Ʈ �ڵ� NValue Get
	NValue = TestDataComponent->GetTestData().CourseInfo.Num();
	InitMoverSpawnTimes(NValue);
}

void ASimulatorManager::ReleaseActor()
{
	auto Iter = Movers.CreateIterator();

	// Mover & DestSign ���� ����
	for (; Iter; ++Iter)
	{
		if (false == Iter->Value->bIsAllowDestroy)
		{
			++Iter;
			continue;
		}
		
		// �����ϰ��� �ϴ� Mover���� ���� Key(=first)���� ����
		// DestSigns ���� �Ȱ��� Key ���� �Ҵ� �Ǿ� �ֱ� ������ DestroyKey�� ���� ����
		TObjectPtr<AMover> DestroyMover = Movers.Find(Iter->Key)->Get();
		int DestroyKey = *Movers.FindKey(DestroyMover);

		// bIsAllowDestroy ������ true�̸� �����ص� �ȴٴ� �ǹ�
		// Mover ����
		Movers.Find(Iter->Key)->Get()->Destroy();
		Movers.Remove(Iter->Key);
		
		// DestSign ����
		DestSigns.Find(DestroyKey)->Get()->Destroy();
		DestSigns.Remove(DestroyKey);

		// Destroy Count�� �߰�
		++DestroyCount;
	}
}

// Called every frame
void ASimulatorManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (true == bIsMoversSpawnable)
	{
		SpawnMoverRepeatedly(DeltaTime);
	}

	// ������ ������ ���� �Լ� �ȿ��� ������ ����
	ReleaseActor();
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
		// Mover���� ID�� �ο��Ѵ�.
		Obj->SetID(_MoverID);

		// �ʱ� ������ ��ǥ ��ǥ�� ���� (Test��)
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

		// Mover ���� �� DestSign ���� ����
		FVector2D DestPos2D = Obj->GetSettingData()->WayPointsInfo[Obj->GetSettingData()->WayPointsInfo.Num() - 1];
		FVector DestPos = FVector(DestPos2D.X, DestPos2D.Y, .0);
		SpawnDestSign(DestPos, _MoverID);

		// Mover ���� �� ���� �ð� ���
		FDateTime CurTime = Inst->GetTimeValue();
		Obj->UpdateWidgetTimeInfo(CurTime, EMoverInfoIdx::StartTime);
		Obj->SettingData->StartTime = CurTime.ToString(TEXT("%H:%M:%S"));
	}

}

void ASimulatorManager::SpawnDestSign(FVector _Pos, int _MoverID)
{
	if (nullptr != DestSignClass)
	{
		FTransform TransValue = FTransform(FRotator(.0f, .0f, .0f), _Pos, FVector(1.0f, 1.0f, 1.0f));
		ADestSign* Obj = GetWorld()->SpawnActor<ADestSign>(DestSignClass, TransValue);
		// Mover���� ID�� �ο��Ѵ�.
		Obj->SetID(_MoverID);

		DestSigns.Add(_MoverID) = Obj;
	}
}

void ASimulatorManager::SpawnMoverRepeatedly(float _DeltaTime)
{
	SpawnMoverDeltatime += _DeltaTime;

	if (SpawnMoverDeltatime >= MoverSpawnTimes[MoverSpawnCount])
	{
		UMainGameInstance* Inst = UGlobalFunctonLibrary::GetMainGameInstance(GetWorld());

		// ���� ����ؼ� Mover �ʱ� ��ġ�� �������ش�.
		FVector2D InitPos = CalMoverInitPos(Inst->GetGridUnitValue(), NValue, MoverSpawnCount);

		int RobotID = TestDataComponent->GetTestData().CourseInfo[MoverSpawnCount].MoverID;
		// ���� ID�� TestData���� �������� �ִ�.
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

	// unreal ���� ��ǥ�� �ݿ� �ʿ�
	Result.Y = Base + _Pos.Y * _GridUnitVal;
	Result.X = Base + ((_N - 1 - _Pos.X) * _GridUnitVal);

	return Result;
}

void ASimulatorManager::SendTargetPosInfoToMover(int _MoverID, FVector _TargetPos)
{
	// �̵��ؾ� �� �������� ���� �κ��� �������� �ѹ��� �̵��� ��ġ�� ���

	// �ڷᱸ���� _MoverID�� ��Ī�Ǵ� �����Ͱ� ������ ���� ����
	if (nullptr != Movers.FindChecked(_MoverID))
	{
		Movers.Find(_MoverID)->Get()->SetTargetPos(_TargetPos);
	}
}
