// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/UI/ClientPlayMainWidget.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"


void UClientPlayMainWidget::AddLogText(const FString& _Log)
{
	if (nullptr != LoggingBox)
	{
		UTextBlock* NewText = NewObject<UTextBlock>(this);
		
		if (nullptr != NewText)
		{
			NewText->SetText(FText::FromString(_Log));
			LoggingBox->AddChild(NewText);
		}
	}
}
