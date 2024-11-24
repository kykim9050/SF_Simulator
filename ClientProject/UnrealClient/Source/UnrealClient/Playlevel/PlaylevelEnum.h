// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlaylevelEnum.generated.h"

/**
 * Playlevel 내의 Enum 모음
 */

UENUM(BlueprintType)
enum class EMoverState : uint8
{
	Idle UMETA(Displayname = "Idle"),
	Accel UMETA(Displayname = "Acceleration"),
	Decel UMETA(Displayname = "Deceleration"),
	Rotate UMETA(Displayname = "Rotation"),
	Finish UMETA(Displayname = "Mission Complete"),
};

UENUM(BlueprintType)
enum class EMoverDir : uint8
{
	None,
	E UMETA(Displayname = "East"),
	W UMETA(Displayname = "West"),
	S UMETA(Displayname = "South"),
	N UMETA(Displayname = "North"),
};

UENUM(BlueprintType)
enum class EMoverInfoIdx : uint8
{
	CurPos UMETA(Displayname = "Current Pos Value"),
	DestPos UMETA(Displayname = "Next Destination Pos"),
	StartTime UMETA(Displayname = "Moving Start Time"),
	EndTime UMETA(Displayname = "Moving End Time"),
	End,
};