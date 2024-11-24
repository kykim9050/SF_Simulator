// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/UI/MoverInfoWidget.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"

void UMoverInfoWidget::PosUpdate(const FString& _NewPos, int32 _Type)
{
	UWidget* Widget = InfoList->GetChildAt(_Type);

	if (nullptr != Widget)
	{
		UTextBlock* TextBlock = Cast<UTextBlock>(Widget);

		if (nullptr != TextBlock)
		{
			TextBlock->SetText(FText::FromString(_NewPos));
		}
	}
}

