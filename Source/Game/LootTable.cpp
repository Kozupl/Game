// Fill out your copyright notice in the Description page of Project Settings.


#include "LootTable.h"

int32 ULootTable::RollForItem(float chance) const 
{
	int32 result = (int32)chance / 100; // chance above 100% means that item will surely drop n times, where is the integer part of a division : n = chance / 100
	chance -= result; 

	if (FMath::FRandRange(0.0f, 1.0f) < chance/100)//actual roll for item drop happens here
		result++;// if roll sucseed - 1 more item will be created

	return result;
}

void ULootTable::ConstructLoot(FEquipmentData* LootDropped, int32 LootAmount) const
{
	
}

void  ULootTable::DropLoot(TArray<FEquipmentData>& LootDropped) const // add loot to given array
{
		for (TPair <FEquipmentData, float> Loot : PredefinedLoot) 
		{
			int32 LootAmount = RollForItem(Loot.Value);

			for (int i = 0; i < LootAmount; i++)
				LootDropped.Add(Loot.Key);
		}
}

