// Fill out your copyright notice in the Description page of Project Settings.


#include "Active_Ability.h"
#include "AttributeSet.h"


const FGameplayTagContainer* UActive_Ability::GetCooldownTags() const
{
	FGameplayTagContainer* MutableTags = const_cast<FGameplayTagContainer*>(&TempCooldownTags);
	MutableTags->Reset(); // MutableTags writes to the TempCooldownTags on the CDO so clear it in case the ability cooldown tags change (moved to a different slot)
	const FGameplayTagContainer* ParentTags = Super::GetCooldownTags();
	if (ParentTags)
	{
		MutableTags->AppendTags(*ParentTags);
	}
	MutableTags->AppendTags(CooldownTags);
	return MutableTags;
}

void UActive_Ability::ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	UGameplayEffect* CooldownGE = GetCooldownGameplayEffect();
	if (CooldownGE)
	{
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(CooldownGE->GetClass(), GetAbilityLevel());
		SpecHandle.Data.Get()->DynamicGrantedTags.AppendTags(CooldownTags);
		SpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Cooldown")), CooldownDuration.GetValueAtLevel(GetAbilityLevel()));
		ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
	}
}

void UActive_Ability::SetCooldownDuration(FScalableFloat NewCooldownDuration)
{
	CooldownDuration = NewCooldownDuration;
}

UGameplayEffect* UActive_Ability::GetCostGameplayEffect() const 
{
	UGameplayEffect* GECost = NewObject<UGameplayEffect>(GetTransientPackage(), FName(TEXT("Cost")));
	GECost->DurationPolicy = EGameplayEffectDurationType::Instant;

	int32 Idx = GECost->Modifiers.Num();
	GECost->Modifiers.SetNum(Idx + 1);

	FGameplayModifierInfo& CostModifiers = GECost->Modifiers[Idx];
	CostModifiers.ModifierMagnitude = FScalableFloat(Cost.GetValueAtLevel(GetAbilityLevel()));//didn't get where is coeficient should be set
	CostModifiers.ModifierOp = EGameplayModOp::Additive;
	CostModifiers.Attribute = CostAttribute;

	return GECost;
}