// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/UI/ClientPlayHUD.h"
#include "Playlevel/UI/ClientPlayMainWidget.h"

void AClientPlayHUD::BeginPlay()
{
	Super::BeginPlay();

	MainWidget = CreateWidget<UClientPlayMainWidget>(GetWorld(), MainWidgetClass);

	if (nullptr != MainWidget)
	{
		MainWidget->AddToViewport();
	}
}
