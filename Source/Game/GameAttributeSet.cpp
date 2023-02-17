// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Characters_Interface.h"
#include "GenericPlatform/GenericPlatformMath.h"

UGameAttributeSet::UGameAttributeSet() {}

bool UGameAttributeSet::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) // Called just before modifying the value of an attribute. AttributeSet can make additional modifications here. Return true to continue, or false to throw out the modification
{//Use to prevent impossible changes, e.g. heal over max health. Generaly for meta attributes
    Super::PreGameplayEffectExecute(Data);

    FGameplayAttribute Attribute = Data.EvaluatedData.Attribute;
    float const Magnitude = Data.EvaluatedData.Magnitude;

    if (Attribute == GetCurrentHealthAttribute())//doesn't apply heal, if hp is max
    {
        if (GetCurrentHealth() == GetMaxHealth() || GetCurrentHealth() == 0.f)//I think, I should handle dead case by tag, instead of by 0 health value
            if (Magnitude > GetCurrentMana())
                return false;
    }
    else if (Attribute == GetCurrentManaAttribute())
    {
        if (GetCurrentMana() >= GetMaxMana() && Magnitude > GetCurrentMana()) // if mana is full, don't restore more
            return false;
    }
        return true;
}

void UGameAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) //This is lower level than PreAttributeModify/PostAttribute modify. This function is meant to enforce things like clamping and NOT things like "trigger this extra thing if damage is applied, etc". 
{//Use for clamping, generaly

    Super::PreAttributeChange(Attribute, NewValue);

    if (Attribute == GetCurrentHealthAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
    }
    else if (Attribute == GetCurrentManaAttribute()) 
    {
        NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
    }
    else if (Attribute == GetMaxHealthAttribute())
    {
        NewValue = FMath::Max(NewValue, 0.f);
        ScaleAttributeToNewMaxValue(CurrentHealth, MaxHealth, NewValue, GetCurrentHealthAttribute());//mb should do this in PostGameplayEffectExecute
    }
    else if (Attribute == GetMaxManaAttribute())
    {
        NewValue = FMath::Max(NewValue, 0.f);
        ScaleAttributeToNewMaxValue(CurrentMana, MaxMana, NewValue, GetCurrentManaAttribute());
    }
}

void UGameAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{//Use for attributes effect, e.g. levelup or death
    
	Super::PostGameplayEffectExecute(Data);
    FGameplayAttribute AttributeChanged = Data.EvaluatedData.Attribute;

	if (AttributeChanged == GetCurrentHealthAttribute())//Damage
	{

        //if killed,die
        if (GetCurrentHealth() <= 0.f)
        {
            //AActor* SourceActor = Data.EffectSpec.GetEffectContext().GetOriginalInstigator();
            AActor* TargetActor = GetTargetActor(&Data);
            AActor* SourceActor = GetSourceActor(&Data);
            
            if (SourceActor) {
                //Check does actor implements interface
                if (Data.Target.GetOwnerActor()->GetClass()->ImplementsInterface(UCharacters_Interface::StaticClass()))
                    ICharacters_Interface::Execute_Die(Data.Target.GetOwnerActor(), SourceActor);
            }
        }
	}
    else if (AttributeChanged == GetCurrentExpAttribute())
    {
        while (GetCurrentExp() > GetExpForNextLvl())
        {
            SetCurrentExp(GetCurrentExp() - GetExpForNextLvl());
            SetLevel(GetLevel() + 1.f);
        }
    }

}

void UGameAttributeSet::SetExpForNextLvl()
{
    // Make sure we have an Ability System Component instance. This should always be the case.
    UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
    if (ensure(ASC))
    {
        float NewVal = pow(((GetLevel() - 1.f) * 10.f), 1.5f);
        //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("SetExpForNextLvl-: %f"), NewVal));
        ASC->SetNumericAttributeBase(GetExpForNextLvlAttribute(), NewVal);
    }
}

void UGameAttributeSet::SetLevel(float NewVal)
{
    // Make sure we have an Ability System Component instance. This should always be the case.
    UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
    if (ensure(ASC))
    {
        // Set the base value (not the current value) through the appropriate function.
        // This makes sure that any modifiers we have applied will still work properly.
        ASC->SetNumericAttributeBase(GetLevelAttribute(), NewVal);
        SetExpForNextLvl();
    }
}

void UGameAttributeSet::ScaleAttributeToNewMaxValue(const FGameplayAttributeData& CurrentAttribute, const FGameplayAttributeData& MaxAttribute, const float NewMaxValue, const FGameplayAttribute& CurrentAttributeProperty)
{
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
    if (CurrentMaxValue != NewMaxValue && AbilityComp)
    {
        const float CurrentValue = CurrentAttribute.GetCurrentValue();
        float Delta = (CurrentMaxValue > 0.f) ? (CurrentValue * ((NewMaxValue / CurrentMaxValue) - 1)): NewMaxValue;

        AbilityComp->ApplyModToAttributeUnsafe(CurrentAttributeProperty, EGameplayModOp::Additive, Delta);
    }
}

AActor* UGameAttributeSet::GetTargetActor(const FGameplayEffectModCallbackData* Data) const
{
    AActor* TargetActor = nullptr;
    if (Data->Target.AbilityActorInfo.IsValid() && Data->Target.AbilityActorInfo->AvatarActor.IsValid())
        TargetActor = Data->Target.AbilityActorInfo->AvatarActor.Get();

    return TargetActor;

}

AActor* UGameAttributeSet::GetSourceActor(const FGameplayEffectModCallbackData* Data) const 
{
    UAbilitySystemComponent* Source = Data->EffectSpec.GetContext().GetOriginalInstigatorAbilitySystemComponent();
    AActor* SourceActor = nullptr;
    if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
        SourceActor = Source->AbilityActorInfo->AvatarActor.Get();

    return SourceActor;
}