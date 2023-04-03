// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAttributeHelper.h"
#include "GameAttributeSet.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"

UCustomAttributeHelper::UCustomAttributeHelper()
{

}

FGameplayAttribute UCustomAttributeHelper::GetAttributeByName(FName PropertyName)
{
	static  FProperty* Prop = FindFieldChecked<FProperty>(UGameAttributeSet::StaticClass(), PropertyName);
	//didn't I create a UGameAttributeSet every time this method is called? Well, it's STATIC class, so I shouldn't
	return Prop;
}

FEquipmentData::FEquipmentData()
{
	Name = FName(TEXT("Bob"));
	Type = FGameplayTag();//FGameplayTag::RequestGameplayTag(FName("State.Dead"));
	MainAttributes.Add(FName (TEXT("MaxHealth")), 10);
	SecondaryAttributes.Add(FName(TEXT("MaxMana")), 10);
	Rarity = ERarity::RE_Common;
	Appearance = nullptr;
	//static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/InfinityBladeWeapons/Weapons/Blunt/Blunt_BoneShard/StaticMesh/SM_Blunt_BoneShardMace.SM_Blunt_BoneShardMace'"));
	//Appearance = MeshAsset.Object;
}

FEquipmentData::FEquipmentData(FName Name, FName TypeTagName, TMap<FName, float> MainAttributes, TMap<FName, float> SecondaryAttributes, ERarity Rarity, UStaticMesh* Appearance)
{
	this->Name = Name;
	this->Type = FGameplayTag::RequestGameplayTag(FName(TypeTagName));
	this->MainAttributes = MainAttributes;
	this->SecondaryAttributes = SecondaryAttributes;
	this->Rarity = Rarity;
	this->Appearance = Appearance;
}

int32 FEquipmentData::GetAttributesNumber() const
{
	int32 Num;
	Num = MainAttributes.Num() + SecondaryAttributes.Num();
	return Num;
}

FRandomLoot::FRandomLoot()
{
	Type = FGameplayTag::RequestGameplayTag(FName("Equipment.Head"));
	Rarity = ERarity::RE_Common;
	Level = 1;
}

FRandomLoot::FRandomLoot(FName TypeTagName, ERarity Rarity, int32 level)
{
	this->Type = FGameplayTag::RequestGameplayTag(TypeTagName);
	this->Rarity = Rarity;
	Level = level;
}