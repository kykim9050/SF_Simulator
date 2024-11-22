// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/Actor/Mover.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Playlevel/Base/BaseMoverAIController.h"


// Sets default values
AMover::AMover()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Mover ������ �ݸ����� ���ܵ� ��ġ ������ �� �� ���� ���
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	MoverMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MoverMeshComponent"));
	HedingComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("HedingComponent"));
}

// Called when the game starts or when spawned
void AMover::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorScale3D(FVector(.5f, .5f, .5f));

	// AI Controller ����
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
	
}

// Called every frame
void AMover::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMover::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

