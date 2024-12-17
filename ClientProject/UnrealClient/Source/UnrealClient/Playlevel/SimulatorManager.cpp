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

	// Mover & DestSign 삭제 로직
	for (; Iter; ++Iter)
	{
		if (false == Iter->Value->bIsAllowDestroy)
		{
			++Iter;
			continue;
		}
		
		// 삭제하고자 하는 Mover에서 실제 Key(=first)값을 추출
		// DestSigns 에도 똑같은 Key 값에 할당 되어 있기 때문에 DestroyKey로 삭제 가능
		TObjectPtr<AMover> DestroyMover = Movers.Find(Iter->Key)->Get();
		int DestroyKey = *Movers.FindKey(DestroyMover);

		// bIsAllowDestroy 변수가 true이면 삭제해도 된다는 의미
		// Mover 삭제
		Movers.Find(Iter->Key)->Get()->Destroy();
		Movers.Remove(Iter->Key);
		
		// DestSign 삭제
		DestSigns.Find(DestroyKey)->Get()->Destroy();
		DestSigns.Remove(DestroyKey);

		// Destroy Count에 추가
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

	// 안전한 삭제를 위해 함수 안에서 별도로 구현
	ReleaseActor();
}

void ASimulatorManager::ObjectPosInitRandomly(TArray<int>& _Array, int32 _N)
{
	for (int32 i = 0; i < _N; ++i)
	{
		_Array.Add(i + 1);
	}

	// 배열의 순서를 랜덤하게 섞기
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

	// Mover 초기 위치 관련 정보 랜덤 구현
	ObjectPosInitRandomly(MoversInitPosSource, NValue);

	// 초기화된 NValue 갑으로 스폰할 시간 배열 생성
	InitMoverSpawnTimes(NValue);

	// 그리드 생성
	SpawnGridPlatform(_Pos);

	// DestSign 초기 위치 관련 정보 랜덤 구현
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

		// Mover 생성 위치 좌표 변환
		FVector2D StartPos = CalMoverInitPos(Inst->GetGridUnitValue(), NValue, MoverSpawnCount);

		FTransform TransValue = FTransform(FRotator(.0f, .0f, .0f), FVector(StartPos.X, StartPos.Y, 100.0f), FVector(1.0f, 1.0f, 1.0f));
		AMover* Obj = GetWorld()->SpawnActor<AMover>(MoverClass, TransValue);
		// Mover에게 ID를 부여한다.
		Obj->SetID(_MoverID);


		// Mover 생성 시 DestSign 동시 생성
		// DestSign의 위치 좌표 생성
		FVector DestPos = FVector();
		int32 DestIdx = 0;
		for (; DestIdx < DestSignsInitPosSource.Num(); DestIdx++)
		{
			// Mover의 ID와 같다면 해당 위치에 DestSign 생성
			if (_MoverID == DestSignsInitPosSource[DestIdx])
			{
				FVector2D DestPos2D = CalDestSignInitPos(Inst->GetGridUnitValue(), NValue, DestIdx);
				DestPos = FVector(DestPos2D.X, DestPos2D.Y, .0);
				SpawnDestSign(DestPos, _MoverID);
				break;
			}
		}

		// 간단한 정수로의 목적지 좌표 전달
		int32 iStartXPos = StaticCast<int32>(_Pos.X);
		int32 iStartYPos = StaticCast<int32>(_Pos.Y);
		int32 iDestXPos = 0;

		// [ID, Mover 초기 위치, DestSign 초기 위치] payload 추합
		FArrayWriter WriteArray;
		WriteArray << _MoverID;
		WriteArray << iStartXPos;
		WriteArray << iStartYPos;
		WriteArray << iDestXPos;
		WriteArray << DestIdx;

		// 패킷 생성
		TSharedPtr<FBufferArchive> Packet = UClientPacketManager::CreateRequestPacket(EPacketType::MoverCoursePacket, WriteArray);
		//AClientPlayGameMode* CurGameMode = UGlobalFunctonLibrary::GetClientPlayGameMode(GetWorld());
		//if (CurGameMode)
		//{
		//	// 서버로 패킷 송신
		//	CurGameMode->GetTCPClient()->SendData(*(Packet.Get()));
		//}

		//// 초기 생성시 목표 좌표를 전달 (Test용)
		//int Size = TestDataComponent->GetTestData().CourseInfo[MoverSpawnCount].CourseArray.Num();

		//// Mover에게 이동할 경로를 제공한다.
		//TArray<FVector2D> ConvertPathInfo = TArray<FVector2D>();
		//for (int i = 0; i < Size; i++)
		//{
		//	FVector2D Vector = TestDataComponent->GetTestData().CourseInfo[MoverSpawnCount].CourseArray[i];
		//	ConvertPathInfo.Add(Vector);
		//}
		//// 경로를 Mover에 보내기전에 경로를 요약한다. (꺾이는 부분이 어딘지를 기준으로, 실제 좌표로)
		//TArray<FVector2D> ModyfiedPathInfo = PathModify(ConvertPathInfo);

		//Obj->SetWayPoints(ModyfiedPathInfo);
		Movers.Add(_MoverID) = Obj;

		// Mover 생성 시 생성 시간 기록
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
		// Mover에게 ID를 부여한다.
		Obj->SetID(_MoverID);

		DestSigns.Add(_MoverID) = Obj;
	}
}

void ASimulatorManager::SpawnMoverRepeatedly(float _DeltaTime)
{
	SpawnMoverDeltatime += _DeltaTime;

	if (SpawnMoverDeltatime >= MoverSpawnTimes[MoverSpawnCount])
	{
		// 값을 계산해서 Mover 초기 위치를 지정해준다.
		FVector InitPos{ StaticCast<double>(NValue - 1), StaticCast<double>(MoverSpawnCount), 0. };

		// 초기 랜덤하게 섞인 위치 정보에 저장된 ID값 활용
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
				// 압축된 경로에서 실제 좌표로 변환
				FVector2D TransVec = ConvertToRealPos(_Course[i + 1], Inst->GetGridUnitValue(), NValue);
				// 변환된 결과를 대입
				ResCourse.Add(TransVec);
			}
		}
	}
	// 마지막 좌표를 대입 (실좌표로 변환해서)
	ResCourse.Add(ConvertToRealPos(_Course[_Course.Num() - 1], Inst->GetGridUnitValue(), NValue));

	return ResCourse;
}