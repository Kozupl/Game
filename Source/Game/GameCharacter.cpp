// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "LootTable.h"
#include "GameAttributeSet.h"
#include "Loot.h"

AGameCharacter::AGameCharacter()//constructor
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
	EffectRemoveOnDeathTag = FGameplayTag::RequestGameplayTag(FName("Effect.RemoveOnDeath"));

	LootTable = nullptr;
	DeathMontage = nullptr;
}

void AGameCharacter::BeginPlay() 
{
	Super::BeginPlay();
	if (IsValid(AbilitySystemComponent))
	{
		AttributeSet = AbilitySystemComponent->GetSet<UGameAttributeSet>();
		AbilitySystemComponent->InitAbilityActorInfo(GetController(), this);// AbilitySystemComponent initialization.
		//Actor controller will be owner of AbilitySystemComponent, and character will be avatar
	}
	//Attribute change callbacks
	/*CurrentHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate
	(AttributeSet->GetCurrentHealthAttribute()).AddUObject(this, &AGameCharacter::CurrentHealthChanged);*/

}

void AGameCharacter::GrandAbility(TSubclassOf <UGameplayAbility> AbilityClass, int32 AbilityLevel, int32 InputCode) const 
{
	if (GetLocalRole() == ROLE_Authority && IsValid(AbilitySystemComponent) && IsValid(AbilityClass))
	{
		UGameplayAbility* Ability = AbilityClass->GetDefaultObject<UGameplayAbility>();

		if (IsValid(Ability)) 
		{
			FGameplayAbilitySpec AbilitySpec(Ability, AbilityLevel, InputCode);

			AbilitySystemComponent->GiveAbility(AbilitySpec);
		}
	}
}

				/*Attributes Values Handlers*/

float AGameCharacter::GetMaxHealth() const
{
	if (IsValid(AbilitySystemComponent))
	{
		return AttributeSet->GetMaxHealth();
	}

	return -1.0f;
}

float AGameCharacter::GetCurrentHealth() const
{
	if (IsValid(AbilitySystemComponent))
	{
		return AttributeSet->GetCurrentHealth();
	}

	return -1.0f;
}


float AGameCharacter::GetAttackPower() const
{
	if (IsValid(AbilitySystemComponent))
	{
		return AttributeSet->GetAttackPower();
	}

	return 0.f;
}

/*void AGameCharacter::CurrentHealthChanged(const FOnAttributeChangeData& Data)
{
	CurrentHealthChangedDelegateHandle.Broadcast(Data.NewValue);
}*/

//Interface functions
void AGameCharacter::AttackTarget_Implementation(UAbilitySystemComponent* ASC) {}

void AGameCharacter::UseAbility_Implementation() {}

void AGameCharacter::UseDash_Implementation() {}

void AGameCharacter::RemoveCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !IsValid(AbilitySystemComponent))
	{
		return;
	}

	// Remove any abilities added from a previous call. This checks to make sure the ability is in the startup 'CharacterAbilities' array.
	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
	for (const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if ((Spec.SourceObject == this) && CharacterAbilities.Contains(Spec.Ability->GetClass()))
		{
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}

	// Do in two passes so the removal happens after we have the full list
	for (int32 i = 0; i < AbilitiesToRemove.Num(); i++)
	{
		AbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);
	}
}

void AGameCharacter::Die_Implementation(AActor* Killer)
{
	// Only runs on Server
	RemoveCharacterAbilities();

	//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale = 0;
	GetCharacterMovement()->Velocity = FVector(0);

	//OnCharacterDied.Broadcast(this);

	if (IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->CancelAllAbilities();

		FGameplayTagContainer EffectTagsToRemove;
		EffectTagsToRemove.AddTag(EffectRemoveOnDeathTag);
		int32 NumEffectsRemoved = AbilitySystemComponent->RemoveActiveEffectsWithTags(EffectTagsToRemove);

		//AbilitySystemComponent->AddLooseGameplayTag(DeadTag);
	}

	if (DeathMontage)
	{
		PlayAnimMontage(DeathMontage);
	}
	else
	{
		FinishDying();
	}
}

void AGameCharacter::FinishDying()
{
	Destroy();
}

bool AGameCharacter::IsAlive() const 
{
	return GetCurrentHealth() != 0.f;
}

void AGameCharacter::DropLoot() const 
{
	TArray<FEquipmentData> LootBag;//mb call LootBag.Empty() before passing into DropLoot()?
	//LootBag.Empty();
	LootTable->DropLoot(LootBag);
	/*for (FEquipmentData EquipmentData : LootBag) {
		ALoot Loot = ALoot(EquipmentData);
		const FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation(0.0f, 0.0f, 0.0f);
		const FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
		GetWorld()->SpawnActor<ALoot>(SpawnLocation, SpawnRotation, SpawnParameters);
	}*/
}