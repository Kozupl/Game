
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
//#include <GameplayEffectTypes.h>
#include "GameplayTagContainer.h"
#include "GameAttributeSet.h"
#include "AsyncTaskAttributeChanged.h"
#include "Characters_Interface.h"
#include "GameCharacter.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttributeChangedDelegate, float, OldValue, float, NewValue, FGameplayAttribute, Attribute);

UCLASS(Blueprintable)
class AGameCharacter : public ACharacter, public IAbilitySystemInterface, public ICharacters_Interface
{

private:

	GENERATED_BODY()
		//Constructor
	AGameCharacter();

	UFUNCTION(BlueprintCallable, Category = "Abilities")
		void GrandAbility(TSubclassOf <UGameplayAbility> AbilityClass, int32 AbilityLevel, int32 InputCode) const;

	UPROPERTY()
		const class UGameAttributeSet* AttributeSet;

	// Removes all CharacterAbilities. Can only be called by the Server. Removing on the Server will remove from Client too.
	virtual void RemoveCharacterAbilities();


protected:

	// Death Animation
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation")
		UAnimMontage* DeathMontage;

public:
			//Event BeginPlay
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation")
		class UDataTable* LootDrops;

			//Attributes Handlers
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
		class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Attributes|Listening")
		TArray<FGameplayAttribute> AttributesToListen;

	// Default abilities for this Character. These will be removed on Character death and regiven if Character respawns.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
		TArray<TSubclassOf<class UGameplayAbility>> CharacterAbilities;

	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	UFUNCTION(BlueprintPure, Category = "Attributes")
		float GetMaxHealth() const ;
	UFUNCTION(BlueprintPure, Category = "Attributes")
		float GetCurrentHealth() const;
	UFUNCTION(BlueprintPure, Category = "Attributes")
		float GetAttackPower() const;

	UFUNCTION(BlueprintPure, Category = "State")
		bool IsAlive() const;

	//Property change 
	//virtual void CurrentHealthChanged(const FOnAttributeChangeData& Data);
	/*UPROPERTY(BlueprintAssignable, Category = "Attribute callbacks")
		FAttributeChangedDelegate OnAttributeChanged;*/
		

	UFUNCTION(BlueprintCallable, Category = "Character")
		virtual void FinishDying();

	//Interface functions

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void UseAbility();
	virtual void UseAbility_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void UseDash();
	virtual void UseDash_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void AttackTarget(UAbilitySystemComponent* ASC);
	virtual void AttackTarget_Implementation(UAbilitySystemComponent* ASC) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Die(AActor* Killer);
	virtual void Die_Implementation(AActor* Killer) override;

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }


};