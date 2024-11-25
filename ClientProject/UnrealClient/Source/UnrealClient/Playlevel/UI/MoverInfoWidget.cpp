// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/UI/MoverInfoWidget.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"

void UMoverInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	WidgetInitSetting();
}

void UMoverInfoWidget::WidgetInitSetting()
{
	if (nullptr != BackGroundBorder)
	{
		BackGroundBorder->SetBrushColor(FLinearColor(FVector4f(0.f, 0.f, 0.f, 0.35f)));
	}

	UTextBlock* DestPosText = GetInfoListChildAt<UTextBlock>(EMoverInfoIdx::DestPos);
	if (nullptr != DestPosText)
	{
		DestPosText->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
	}

	UTextBlock* StartTimeText = GetInfoListChildAt<UTextBlock>(EMoverInfoIdx::StartTime);
	if (nullptr != StartTimeText)
	{
		StartTimeText->SetColorAndOpacity(FSlateColor(FLinearColor::Green));
	}

	UTextBlock* EndTimeText = GetInfoListChildAt<UTextBlock>(EMoverInfoIdx::EndTime);
	if (nullptr != EndTimeText)
	{
		EndTimeText->SetText(FText::FromString(TEXT("")));
		EndTimeText->SetColorAndOpacity(FSlateColor(FLinearColor::Green));
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