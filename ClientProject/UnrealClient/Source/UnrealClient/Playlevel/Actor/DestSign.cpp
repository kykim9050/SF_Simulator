// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/Actor/DestSign.h"

// Sets default values
ADestSign::ADestSign()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IDComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("IDComponent"));
}

// Called when the game starts or when spawned
void ADestSign::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestSign::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

