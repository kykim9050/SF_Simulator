// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ClientPlayBaseUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCLIENT_API UClientPlayBaseUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:

protected:
	const FText GetPaletteCategory() override;

private:
	
};
