// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ClientPlayMainWidget.generated.h"

/**
 * Playlevel �c�鿡 ǥ���� ���� ��ҵ��� �����ϴ� ���� ����
 */
class UCanvasPanel;
class UWidgetSwitcher;
UCLASS()
class UNREALCLIENT_API UClientPlayMainWidget : public UUserWidget
{
	GENERATED_BODY()
public:

protected:
	const FText GetPaletteCategory() override;

private:
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UCanvasPanel* RootWidget = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UWidgetSwitcher* WidgetSwitcher = nullptr;
};
