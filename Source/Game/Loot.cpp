// Fill out your copyright notice in the Description page of Project Settings.


#include "Loot.h"
#include "Components/StaticMeshComponent.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "GameAttributeSet.h"
#include "Components/Image.h"

// Sets default values
ALoot::ALoot()
{
	PrimaryActorTick.bCanEverTick = true;
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Body;
	Name = FName(TEXT("Bob"));
	Type = EEquipmentType::Ring;
	LootIcon = nullptr;
	Rarity = ERarity::RE_Rare;
	ItemDescription = FText::FromString(TEXT("Item description here"));
}

// Called when the game starts or when spawned
void ALoot::BeginPlay()
{
	Super::BeginPlay();
}

FName ALoot::GetGEName() const
{
	static int32 EquipementGENameOffsetNumber = 0;
	FName GEName = FName("RuntimeGE_" + GetNameSafe(this) + FString::FromInt(EquipementGENameOffsetNumber));

	EquipementGENameOffsetNumber++;
	return GEName;
}

/*void ALoot::Equip(UAbilitySystemComponent* EquiperASC) //temporary disabled 
{
	if (EquiperASC)
	{
		UGameplayEffect* EquipGE =NewObject<UGameplayEffect>(GetTransientPackage(), GetGEName());

		EquipGE->DurationPolicy = EGameplayEffectDurationType::Infinite;

		int32 i = EquipGE->Modifiers.Num();
		EquipGE->Modifiers.SetNum(i + EquipmentData.GetAttributesNumber());

		int tempIdxDisplacement = 0;
		TMap<EEquipmentAttributes, float> Attributes = EquipmentData.MainAttributes;// creating coppy of attributes maps
		for (const TPair<EEquipmentAttributes, float>& pair : Attributes)
		{
			FGameplayAttribute Attribute = UCustomAttributeHelper::GetAttributeByEnumName(pair.Key);
			FGameplayModifierInfo& Info = EquipGE->Modifiers[i + tempIdxDisplacement];
			Info.Attribute = Attribute;
			Info.ModifierMagnitude = FScalableFloat(pair.Value);
			Info.ModifierOp = EGameplayModOp::Additive;
			
			FGameplayTagRequirements reqs;
			reqs.IgnoreTags = FGameplayTagContainer();
			reqs.RequireTags = FGameplayTagContainer();

			Info.SourceTags = reqs;
			Info.TargetTags = reqs;

			tempIdxDisplacement++;
		}

		EquipedEffectHandle = EquiperASC->ApplyGameplayEffectToSelf(EquipGE, 1.0f, EquiperASC->MakeEffectContext());
		UE_LOG(LogTemp, Log, TEXT("New GE Handle %s:"), *EquipedEffectHandle.ToString());
	}

}*/