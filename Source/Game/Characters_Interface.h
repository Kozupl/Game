// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Characters_Interface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UCharacters_Interface : public UInterface
{
	GENERATED_BODY()
};

class GAME_API ICharacters_Interface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void UseAbility();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void UseDash();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void ClearTarget();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void AttackTarget(UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		USceneComponent* GetCastPoint();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Die(AActor* Killer);
};
