// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/ClientPlayGameMode.h"
#include "Playlevel/SimulatorManager.h"

void AClientPlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (nullptr != MainSimulatorClass)
	{
		MainSimulator = GetWorld()->SpawnActor<ASimulatorManager>(MainSimulatorClass);
	}
}
