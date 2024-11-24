// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/UI/MoverInfoWidget.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"

void UMoverInfoWidget::CurPosUpdate(const FString& _NewPos)
{
	UWidget* Widget = InfoList->GetChildAt(0);

	if (nullptr != Widget)
	{
		UTextBlock* TextBlock = Cast<UTextBlock>(Widget);

		if (nullptr != TextBlock)
		{
			TextBlock->SetText(FText::FromString(_NewPos));
		}
	}
}
