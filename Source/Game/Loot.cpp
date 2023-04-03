// Fill out your copyright notice in the Description page of Project Settings.


#include "Loot.h"
#include "Components/StaticMeshComponent.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "GameAttributeSet.h"

// Sets default values
ALoot::ALoot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Body->SetStaticMesh(EquipmentData.Appearance);
	RootComponent = Body;
	

	EquipmentData = FEquipmentData();

	if (EquipmentData.Appearance) {
		Body->SetStaticMesh(EquipmentData.Appearance);
		UE_LOG(LogTemp, Error, TEXT("%s"), *EquipmentData.Appearance->GetName());
	}

}

// Called when the game starts or when spawned
void ALoot::BeginPlay()
{
	Super::BeginPlay();
}

FName ALoot::GetGEName() const
{
	static int32 EquipementGENameOffsetNumber = 0;
	FName Name = FName("RuntimeGE_" + GetNameSafe(this) + FString::FromInt(EquipementGENameOffsetNumber));

	EquipementGENameOffsetNumber++;
	return Name;
}

void ALoot::Equip(UAbilitySystemComponent* EquiperASC) 
{
	if (EquiperASC)
	{
		UGameplayEffect* EquipGE =NewObject<UGameplayEffect>(GetTransientPackage(), GetGEName());

		EquipGE->DurationPolicy = EGameplayEffectDurationType::Infinite;

		int32 i = EquipGE->Modifiers.Num();
		EquipGE->Modifiers.SetNum(i + EquipmentData.GetAttributesNumber());

		int tempIdxDisplacement = 0;
		for (const TPair<FName, float>& pair : EquipmentData.MainAttributes)
		{
			FGameplayAttribute Attribute = UCustomAttributeHelper::GetAttributeByName(pair.Key);
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

		for (const TPair<FName, float>& pair : EquipmentData.SecondaryAttributes)
		{
			FGameplayAttribute Attribute = UCustomAttributeHelper::GetAttributeByName(pair.Key);
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

}

