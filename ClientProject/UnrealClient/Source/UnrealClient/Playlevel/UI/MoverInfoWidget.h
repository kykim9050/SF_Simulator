// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Playlevel/Base/ClientPlayBaseUserWidget.h"
#include "Playlevel/UI/IDMainWidget.h"
#include "MoverInfoWidget.generated.h"

/**
 * Mover Info 표시를 위한 전용 위젯
 */
class UCanvasPanel;
class UVerticalBox;
UCLASS()
class UNREALCLIENT_API UMoverInfoWidget : public UClientPlayBaseUserWidget
{
	GENERATED_BODY()
public:
	
	UIDMainWidget* GetIDWidget()
	{
		return IDWidget;
	}

protected:

private:
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UCanvasPanel* RootWidget = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UIDMainWidget* IDWidget = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UVerticalBox* InfoList = nullptr;
};
