// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "CustomAttributeHelper.h"
#include "Loot.generated.h"

UCLASS()
class GAME_API ALoot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALoot();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance")
		class UStaticMeshComponent* Body;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance|Interface")
		class UImage* LootIcon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance|Interface")
		FName Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance|Interface")
		FText ItemDescription;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loot Properties")
		EEquipmentType Type;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loot Properties")
		ERarity Rarity;



protected:

	virtual void BeginPlay() override;

	FName GetGEName() const;//Gives uniquie name for each GA created

public:	

	//void Equip(class UAbilitySystemComponent* EquiperASC);

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		//FActiveGameplayEffectHandle EquipedEffectHandle;

};
