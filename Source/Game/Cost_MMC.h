// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "Cost_MMC.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API UCost_MMC : public UGameplayModMagnitudeCalculation
{

	GENERATED_BODY()

public:
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
