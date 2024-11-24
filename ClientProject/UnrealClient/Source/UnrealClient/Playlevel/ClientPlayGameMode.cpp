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

	if (nullptr != TCPClientClass)
	{
		TCPClient = GetWorld()->SpawnActor<ATCPClient>(TCPClientClass);
		
		if (true == TCPClient->ConnectToServer(FString(TEXT("127.0.0.1")), 30000))
		{
			int a = 0;
		}
	}

}
