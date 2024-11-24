// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/UI/MoverInfoWidget.h"
#include "Components/TextBlock.h"

void UMoverInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	WidgetInitSetting();
}

void UMoverInfoWidget::WidgetInitSetting()
{
	UTextBlock* DestPosText = GetInfoListChildAt<UTextBlock>(EMoverInfoIdx::DestPos);
	if (nullptr != DestPosText)
	{
		DestPosText->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
	}

	UTextBlock* EndTimeTextBlock = GetInfoListChildAt<UTextBlock>(EMoverInfoIdx::EndTime);
	if (nullptr != EndTimeTextBlock)
	{
		EndTimeTextBlock->SetText(FText::FromString(TEXT("")));
	}
}

void UMoverInfoWidget::InfoUpdate(const FString& _NewPos, int32 _Type)
{
	UTextBlock* TextBlock = GetInfoListChildAt<UTextBlock>(_Type);

	if (nullptr != TextBlock)
	{
		TextBlock->SetText(FText::FromString(_NewPos));
	}
}