// Fill out your copyright notice in the Description page of Project Settings.


#include "Cost_MMC.h"
#include "Active_Ability.h"

float UCost_MMC::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const UActive_Ability* Ability = Cast<UActive_Ability>(Spec.GetContext().GetAbilityInstance_NotReplicated());

	if (!Ability)
	{
		return 0.0f;
	}

	return Ability->Cost.GetValueAtLevel(Ability->GetAbilityLevel());
}