// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/Actor/GridPlatform.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AGridPlatform::AGridPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GridMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GridMeshComponent"));
}

// Called when the game starts or when spawned
void AGridPlatform::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGridPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

