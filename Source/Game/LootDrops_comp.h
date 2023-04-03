// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomAttributeHelper.h"
#include "LootDrops_comp.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME_API ULootDrops_comp : public UActorComponent
{
	GENERATED_BODY()

public:	

	ULootDrops_comp();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Drop")
		TMap <FRandomLoot, int32> LootTable;
};