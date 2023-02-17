// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Active_Ability.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API UActive_Ability : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown")
	FScalableFloat CooldownDuration;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Cooldown")
	FGameplayTagContainer CooldownTags;

	// Temp container that we will return the pointer to in GetCooldownTags().
	// This will be a union of our CooldownTags and the Cooldown GE's cooldown tags.
	UPROPERTY(Transient)
	FGameplayTagContainer TempCooldownTags;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Cost")
		FScalableFloat Cost;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Cost")
		FGameplayAttribute CostAttribute;

	virtual const FGameplayTagContainer* GetCooldownTags() const override;

	virtual UGameplayEffect* GetCostGameplayEffect() const override;

	void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;
	
	UFUNCTION(BlueprintCallable, Category = "Cooldown")
	void SetCooldownDuration(FScalableFloat NewCooldownDuration) ;
};
