// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/SimulatorManager.h"
#include "Playlevel/Test/TestDataComponent.h"
#include "Playlevel/Actor/GridPlatform.h"
#include "Playlevel/Actor/Mover.h"
#include "Global/GlobalFunctonLibrary.h"
#include "Playlevel/Actor/DestSign.h"
#include "Global/Net/ClientPacketManager.h"
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

void ASimulatorManager::ObjectPosInitRandomly(TArray<int>& _Array, int32 _N)
{
	for (int32 i = 0; i < _N; ++i)
	{
		_Array.Add(i + 1);
	}

	// �迭�� ������ �����ϰ� ����
	UGlobalFunctonLibrary::ShuffleTArray<int>(_Array);
}

void ASimulatorManager::SpawnGridPlatform(FVector _Pos)
{
	if (nullptr != GridPlatformClass)
	{
		FTransform TransValue = FTransform(FRotator(.0f, .0f, .0f), _Pos, FVector(NValue * 1.0f, NValue * 1.0f, 1.0f));
		GridPlatform = GetWorld()->SpawnActor<AGridPlatform>(GridPlatformClass, TransValue);
	}
}

void ASimulatorManager::GridInit(int32 _N, FVector _Pos)
{
	SetNValue(_N);

	if (5 > NValue && 10 < NValue)
	{
		UE_LOG(LogType, Fatal, TEXT("NValue is not valid"));
		return;
	}

	// Mover �ʱ� ��ġ ���� ���� ���� ����
	ObjectPosInitRandomly(MoversInitPosSource, NValue);

	// �ʱ�ȭ�� NValue ������ ������ �ð� �迭 ����
	InitMoverSpawnTimes(NValue);

	// �׸��� ����
	SpawnGridPlatform(_Pos);

	// DestSign �ʱ� ��ġ ���� ���� ���� ����
	ObjectPosInitRandomly(DestSignsInitPosSource, NValue);
}

void ASimulatorManager::SpawnMover(FVector _Pos, int _MoverID)
{
	if (nullptr != MoverClass)
	{
		UMainGameInstance* Inst = UGlobalFunctonLibrary::GetMainGameInstance(GetWorld());
		if (nullptr == Inst)
		{
			UE_LOG(LogType, Fatal, TEXT("if (nullptr != Inst)"));
			return;
		}

		// Mover ���� ��ġ ��ǥ ��ȯ
		FVector2D StartPos = CalMoverInitPos(Inst->GetGridUnitValue(), NValue, MoverSpawnCount);

		FTransform TransValue = FTransform(FRotator(.0f, .0f, .0f), FVector(StartPos.X, StartPos.Y, 100.0f), FVector(1.0f, 1.0f, 1.0f));
		AMover* Obj = GetWorld()->SpawnActor<AMover>(MoverClass, TransValue);
		// Mover���� ID�� �ο��Ѵ�.
		Obj->SetID(_MoverID);


		// Mover ���� �� DestSign ���� ����
		// DestSign�� ��ġ ��ǥ ����
		FVector DestPos = FVector();
		int32 DestIdx = 0;
		for (; DestIdx < DestSignsInitPosSource.Num(); DestIdx++)
		{
			// Mover�� ID�� ���ٸ� �ش� ��ġ�� DestSign ����
			if (_MoverID == DestSignsInitPosSource[DestIdx])
			{
				FVector2D DestPos2D = CalDestSignInitPos(Inst->GetGridUnitValue(), NValue, DestIdx);
				DestPos = FVector(DestPos2D.X, DestPos2D.Y, .0);
				SpawnDestSign(DestPos, _MoverID);
				break;
			}
		}

		// ������ �������� ������ ��ǥ ����
		int32 iStartXPos = StaticCast<int32>(_Pos.X);
		int32 iStartYPos = StaticCast<int32>(_Pos.Y);
		int32 iDestXPos = 0;

		// [ID, Mover �ʱ� ��ġ, DestSign �ʱ� ��ġ] payload ����
		FArrayWriter WriteArray;
		WriteArray << _MoverID;
		WriteArray << iStartXPos;
		WriteArray << iStartYPos;
		WriteArray << iDestXPos;
		WriteArray << DestIdx;

		// ��Ŷ ����
		TSharedPtr<FBufferArchive> Packet = UClientPacketManager::CreateRequestPacket(EPacketType::MoverCoursePacket, WriteArray);
		//AClientPlayGameMode* CurGameMode = UGlobalFunctonLibrary::GetClientPlayGameMode(GetWorld());
		//if (CurGameMode)
		//{
		//	// ������ ��Ŷ �۽�
		//	CurGameMode->GetTCPClient()->SendData(*(Packet.Get()));
		//}

		//// �ʱ� ������ ��ǥ ��ǥ�� ���� (Test��)
		//int Size = TestDataComponent->GetTestData().CourseInfo[MoverSpawnCount].CourseArray.Num();

		//// Mover���� �̵��� ��θ� �����Ѵ�.
		//TArray<FVector2D> ConvertPathInfo = TArray<FVector2D>();
		//for (int i = 0; i < Size; i++)
		//{
		//	FVector2D Vector = TestDataComponent->GetTestData().CourseInfo[MoverSpawnCount].CourseArray[i];
		//	ConvertPathInfo.Add(Vector);
		//}
		//// ��θ� Mover�� ���������� ��θ� ����Ѵ�. (���̴� �κ��� ������� ��������, ���� ��ǥ��)
		//TArray<FVector2D> ModyfiedPathInfo = PathModify(ConvertPathInfo);

		//Obj->SetWayPoints(ModyfiedPathInfo);
		Movers.Add(_MoverID) = Obj;

		// Mover ���� �� ���� �ð� ���
		FDateTime CurTime = Inst->GetTimeValue();
		Obj->UpdateWidgetTimeInfo(CurTime, EMoverInfoIdx::StartTime);
		FString DateTime = Inst->ConvertToGlobalStandardTime(CurTime);
		Obj->SettingData->StartTime = DateTime;
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
		// ���� ����ؼ� Mover �ʱ� ��ġ�� �������ش�.
		FVector InitPos{ StaticCast<double>(NValue - 1), StaticCast<double>(MoverSpawnCount), 0. };

		// �ʱ� �����ϰ� ���� ��ġ ������ ����� ID�� Ȱ��
		int RobotID = MoversInitPosSource[MoverSpawnCount];
		SpawnMover(InitPos, RobotID);

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

FVector2D ASimulatorManager::CalDestSignInitPos(double _GridUintVal, int _N, int _Idx)
{
	double Base = (-1.0f) * (_GridUintVal * static_cast<double>(_N) / 2.0f) + (_GridUintVal / 2.0f);
	FVector2D RetVal = FVector2D((-1) * Base, Base + _GridUintVal * _Idx);
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

TArray<FVector2D> ASimulatorManager::PathModify(TArray<FVector2D>& _Course)
{
	TArray<FVector2D> ResCourse = TArray<FVector2D>();

	UMainGameInstance* Inst = UGlobalFunctonLibrary::GetMainGameInstance(GetWorld());

	if (nullptr != Inst)
	{
		for (size_t i = 0; i < _Course.Num() - 2; i++)
		{
			if (Inst->CheckDir2D(_Course[i], _Course[i + 1]) != Inst->CheckDir2D(_Course[i + 1], _Course[i + 2]))
			{
				// ����� ��ο��� ���� ��ǥ�� ��ȯ
				FVector2D TransVec = ConvertToRealPos(_Course[i + 1], Inst->GetGridUnitValue(), NValue);
				// ��ȯ�� ����� ����
				ResCourse.Add(TransVec);
			}
		}
	}
	// ������ ��ǥ�� ���� (����ǥ�� ��ȯ�ؼ�)
	ResCourse.Add(ConvertToRealPos(_Course[_Course.Num() - 1], Inst->GetGridUnitValue(), NValue));

	return ResCourse;
}