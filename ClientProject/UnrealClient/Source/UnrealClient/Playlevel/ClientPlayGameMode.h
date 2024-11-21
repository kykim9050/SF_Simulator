// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Base/GlobalGameMode.h"
#include "ClientPlayGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCLIENT_API AClientPlayGameMode : public AGlobalGameMode
{
	GENERATED_BODY()
public:

protected:
	virtual void BeginPlay() override;

private:
	
};
