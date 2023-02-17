// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogGame, Log, All);

UENUM(BlueprintType)
enum class EGameAbilityInputID : uint8 
{
	None,
	Confirm,
	Cancel
};