// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/Actor/Mover.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Playlevel/Base/BaseMoverAIController.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextBlock.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Global/DataTable/MoverDataRow.h"
#include "Global/GlobalFunctonLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Playlevel/Test/TestDataComponent.h"
#include "Playlevel/UI/MoverInfoWidget.h"


// Sets default values
AMover::AMover()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Mover 생성시 콜리전이 생겨도 위치 조정이 된 후 생성 허용
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	MoverMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MoverMeshComponent"));
	IDComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("IDComponent"));

	MoverMeshComponent->SetupAttachment(GetRootComponent());
	IDComponent->SetupAttachment(MoverMeshComponent);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Mover"));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	MoverMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));

	GetCapsuleComponent()->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

// Called when the game starts or when spawned
void AMover::BeginPlay()
{
	Super::BeginPlay();
	
	UMainGameInstance* Inst = UGlobalFunctonLibrary::GetMainGameInstance(GetWorld());
	BaseData = Inst->GetMoverDataRow(StatusName);
	if (nullptr == BaseData)
	{
		UE_LOG(LogType, Fatal, TEXT("if (nullptr == BaseData)"));
		return;
	}

	SetActorScale3D(FVector(.5f, .5f, .5f));

	// AI Controller 세팅
	if (nullptr != MatchingAIControllerClass)
	{
		AIController = GetWorld()->SpawnActor<ABaseMoverAIController>(MatchingAIControllerClass);
		
		if (nullptr == AIController)
		{
			UE_LOG(LogType, Fatal, TEXT("AIController Is Null"));
			return;
		}

		AIController->Possess(this);
	}
	
	// AI데이터 세팅
	{
		SettingData = NewObject<UMoverData>(this);
		SettingData->Data = BaseData;

		ABaseMoverAIController* Con = GetController<ABaseMoverAIController>();
		Con->GetBlackboardComponent()->SetValueAsObject(TEXT("MoverData"), SettingData);
	}

	// id 컴포넌트 세팅
	if (nullptr != IDComponentWidgetClass)
	{
		IDComponent->SetWidgetClass(IDComponentWidgetClass);
		IDComponent->SetDrawSize(FVector2D(150.0f, 50.0f));
		IDComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
		IDComponent->SetWidgetSpace(EWidgetSpace::Screen);
	}

	// 초당 회전 변화량으로 degree인 것으로 보임
	GetCharacterMovement()->RotationRate.Yaw = 10.0f;
}

// Called every frame
void AMover::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateWidgetPosInfo(GetActorLocation(), EMoverInfoIdx::CurPos);
}

// Called to bind functionality to input
void AMover::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMover::SetID(int _ID)
{
	ObjectID::SetID(_ID);

	UUserWidget* Widget = IDComponent->GetWidget();
	if (nullptr != Widget)
	{
		UMoverInfoWidget* IdWidget = Cast<UMoverInfoWidget>(Widget);

		if (nullptr != IdWidget)
		{
			int MyID = GetID();
			FString PrintString = FString(TEXT("M")) + FString::FromInt(MyID);
			FText Text = FText::FromString(PrintString);
			IdWidget->GetIDWidget()->GetIDTextBlock()->SetText(Text);
		}
	}
}

void AMover::SetWayPoints(const TArray<FVector2D>& _WayPointsInfo)
{
	for (size_t i = 0; i < _WayPointsInfo.Num(); ++i)
	{
		SettingData->WayPointsInfo.Add(_WayPointsInfo[i]);
	}
	
	ABaseMoverAIController* Con = GetController<ABaseMoverAIController>();
	Con->GetBlackboardComponent()->SetValueAsObject(TEXT("MoverData"), SettingData);
}

void AMover::UpdateWidgetTimeInfo(EMoverInfoIdx _InfoIdx)
{
	if (nullptr != IDComponent)
	{
		UMoverInfoWidget* InfoWidget = Cast<UMoverInfoWidget>(IDComponent->GetWidget());

		if (nullptr != InfoWidget)
		{
			switch (_InfoIdx)
			{
			case EMoverInfoIdx::StartTime:
			case EMoverInfoIdx::EndTime:
			{
				FString TimeValue = UGlobalFunctonLibrary::GetMainGameInstance(GetWorld())->GetTime();
				InfoWidget->InfoUpdate(TimeValue, _InfoIdx);
				break;
			}
			default:
				break;
			}
		}
	}
}

void AMover::UpdateWidgetPosInfo(FVector _Pos, EMoverInfoIdx _InfoIdx)
{
	if (nullptr != IDComponent)
	{
		UMoverInfoWidget* InfoWidget = Cast<UMoverInfoWidget>(IDComponent->GetWidget());

		if (nullptr != InfoWidget)
		{
			switch (_InfoIdx)
			{
			case EMoverInfoIdx::CurPos:
				InfoWidget->InfoUpdate(FString::Printf(TEXT("Cur Pos : {%.2f, %.2f}"), _Pos.X, _Pos.Y), _InfoIdx);
				break;
			case EMoverInfoIdx::DestPos:
				InfoWidget->InfoUpdate(FString::Printf(TEXT("Next Pos : {%.2f, %.2f}"), _Pos.X, _Pos.Y), _InfoIdx);
				break;
			default:
				break;
			}
		}
	}
}