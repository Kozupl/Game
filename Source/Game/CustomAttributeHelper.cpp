// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAttributeHelper.h"
#include "GameAttributeSet.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"

UCustomAttributeHelper::UCustomAttributeHelper()
{

}

FGameplayAttribute UCustomAttributeHelper::GetAttributeByEnumName(const EEquipmentAttributes& PropertyEnum)
{
	FName PropertyName = FName();
		PropertyName = UEnum::GetValueAsName(PropertyEnum);//Gets name of enum
	//else {
		//UE_LOG(LogTemp, Warning, TEXT("PropertyEnum isn't valid"));
		//PropertyName = FName(TEXT("Invalid"));
	//}
	return GetAttributeByName(PropertyName);
}

// Not sure if this method of getting Attribute does work, becouse of possible inaccuracy in name.
FGameplayAttribute UCustomAttributeHelper::GetAttributeByName(const FName PropertyName)
{
	static FProperty* Prop = FindFieldChecked<FProperty>(UGameAttributeSet::StaticClass(), PropertyName);
	//didn't I create a UGameAttributeSet every time this method is called? Well, it's STATIC class, so I shouldn't
	return Prop;
}

FEquipmentData::FEquipmentData()
{
	Type = EEquipmentType::MainHand;
	MainAttributes.Add(EEquipmentAttributes::Health, 10);
	SecondaryAttributes.Add(EEquipmentAttributes::Mana, 10);
	Rarity = ERarity::RE_Common;
	Name = FName(TEXT("Bob"));
	WorldAppearence = nullptr;
}

FEquipmentData::FEquipmentData(FName Name, EEquipmentType EquipType, TMap<EEquipmentAttributes, float> MainAttributes,
	TMap<EEquipmentAttributes, float> SecondaryAttributes, ERarity Rarity, UStaticMesh* Appearance)
{
	this->Name = Name;
	this->Type = EquipType;
	this->MainAttributes = MainAttributes;
	this->SecondaryAttributes = SecondaryAttributes;
	this->Rarity = Rarity;
	this->WorldAppearence = Appearance;
}

int32 FEquipmentData::GetAttributesNumber() const
{
	int32 Num;
	Num = MainAttributes.Num() + SecondaryAttributes.Num();
	return Num;
}