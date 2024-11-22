// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Playlevel/Base/ClientPlayBaseUserWidget.h"
#include "IDMainWidget.generated.h"

/**
 * ID Á¤º¸¸¦ ¶ç¿ï À§Á¬
 */
class UCanvasPanel;
class UTextBlock;
UCLASS()
class UNREALCLIENT_API UIDMainWidget : public UClientPlayBaseUserWidget
{
	GENERATED_BODY()
public:

	FORCEINLINE UTextBlock* GetIDTextBlock() const
	{
		return ID;
	}

protected:

private:
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UCanvasPanel* RootWidget = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UTextBlock* ID = nullptr;
};
