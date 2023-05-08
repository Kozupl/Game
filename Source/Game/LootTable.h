// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CustomAttributeHelper.h"
#include "LootTable.generated.h"


UCLASS(Blueprintable)
class GAME_API ULootTable : public UDataAsset
{
	GENERATED_BODY()

public:	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Drop")
		TMap <FEquipmentData, float> PredefinedLoot;
	//Value - representing chance of loot drop. Chance of 210% means that 2 items surely drop, and 3-rd whith chance of 10%

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Drop")
		//TMap <FEquipmentData, float> RandomLoot;
	//what if i will use smthg like class instanses(like GA) instead of FEquipmentData as a key? Mb, it could make, creating random item possible


	UFUNCTION(BlueprintPure)
		void DropLoot(TArray<FEquipmentData>& LootDropped) const;

private:

	int32 RollForItem(float chance) const;

	void ConstructLoot(FEquipmentData* LootDropped, int32 LootAmount) const;

}; 