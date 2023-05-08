// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class GAME_API UGameAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UGameAttributeSet();
protected:
				//Attribute Change Handler
	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;

	class AActor* GetTargetActor(const FGameplayEffectModCallbackData* Data) const;

	class AActor* GetSourceActor(const FGameplayEffectModCallbackData* Data) const;

	void ScaleAttributeToNewMaxValue(const FGameplayAttributeData& CurrentAttribute, const FGameplayAttributeData& MaxAttribute, const float NewMaxValue, const FGameplayAttribute& CurrentAttributeProperty);

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes|Modifiers")
		float ExpEfficiency = 0.3;
								/*Properties Handlers*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes|Resources")
		FGameplayAttributeData CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes|Resources")
		FGameplayAttributeData MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes|Resources")
		FGameplayAttributeData CurrentMana;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes|Resources")
		FGameplayAttributeData MaxMana;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes|Resources")
		FGameplayAttributeData HealthRegen;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes|Resources")
		FGameplayAttributeData ManaRegen;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes|Stats")
		FGameplayAttributeData AttackPower;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes|Stats")
		FGameplayAttributeData AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes|Stats")
		FGameplayAttributeData MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes|Stats")
		FGameplayAttributeData AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes|Progress")
		FGameplayAttributeData Level;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes|Progress")
		FGameplayAttributeData ExpForNextLvl;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes|Progress")
		FGameplayAttributeData CurrentExp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes|Progress")
		FGameplayAttributeData ExpBounty;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes|Stats")
		FGameplayAttributeData Defense;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes|Stats")
		FGameplayAttributeData CritChance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes|Stats")
		FGameplayAttributeData CritDamageMultiplayer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes|Stats")
		FGameplayAttributeData MaxMovementSpeed;

	/*Suggested stats:
		Damage Block - blocks exact amount of damage after reducing it
		*Individual Resourses* - e.g. mana for mage, rage for warrior, etc. (questionable)
		Evasion chance
	*/

	/*CurrentHealth*/
	ATTRIBUTE_ACCESSORS(UGameAttributeSet, CurrentHealth);

	/*MaxHealth*/
	ATTRIBUTE_ACCESSORS(UGameAttributeSet, MaxHealth);

	/*Max Mana*/
	ATTRIBUTE_ACCESSORS(UGameAttributeSet, MaxMana);

	/*Current Mana*/
	ATTRIBUTE_ACCESSORS(UGameAttributeSet, CurrentMana);

	/*AttackPower*/
	ATTRIBUTE_ACCESSORS(UGameAttributeSet, AttackPower);

	/*Attack Range*/
	ATTRIBUTE_ACCESSORS(UGameAttributeSet, AttackRange);

	/*Movement Speed*/
	ATTRIBUTE_ACCESSORS(UGameAttributeSet, MovementSpeed);

	/*Attack Speed*/
	ATTRIBUTE_ACCESSORS(UGameAttributeSet, AttackSpeed);

	/*Mana Regen*/
	ATTRIBUTE_ACCESSORS(UGameAttributeSet, ManaRegen);

	/*Health Regen*/
	ATTRIBUTE_ACCESSORS(UGameAttributeSet, HealthRegen);

	/*Level*/
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UGameAttributeSet, Level);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Level);
	void SetLevel(float NewVal);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Level);

	/*Current Exp*/
	ATTRIBUTE_ACCESSORS(UGameAttributeSet, CurrentExp);

	/*Exp required for level up*/
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UGameAttributeSet, ExpForNextLvl);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(ExpForNextLvl);
	void SetExpForNextLvl();
	GAMEPLAYATTRIBUTE_VALUE_INITTER(ExpForNextLvl);

	/*Defence*/
	ATTRIBUTE_ACCESSORS(UGameAttributeSet, Defense);

	/*Chance Of Critical Damage*/
	ATTRIBUTE_ACCESSORS(UGameAttributeSet, CritChance);

	/*Bonus Damage From Critical Strike*/
	ATTRIBUTE_ACCESSORS(UGameAttributeSet, CritDamageMultiplayer);

	/*Maximal Movement Speed*/
	ATTRIBUTE_ACCESSORS(UGameAttributeSet, MaxMovementSpeed);

	/*Exp Bounty for Killing This Creature*/
	ATTRIBUTE_ACCESSORS(UGameAttributeSet, ExpBounty);

};
