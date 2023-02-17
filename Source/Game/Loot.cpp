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
	RootComponent = Body;

	Body->SetSimulatePhysics(true);

}

// Called when the game starts or when spawned
void ALoot::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALoot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALoot::Equip(UAbilitySystemComponent* EquiperASC) const
{
	if (EquiperASC)
	{
		UGameplayEffect* EquipGE = CreateGA(TEXT("Equip_GE"));
		EquiperASC->ApplyGameplayEffectToSelf(EquipGE, 1.f, EquiperASC->MakeEffectContext());
	}
	else 
	{
		return;
	}
}

UGameplayEffect* ALoot::CreateGA(FName Name) const
{
	UGameplayEffect* EquipGE = NewObject<UGameplayEffect>(GetTransientPackage(), FName(Name));

	return EquipGE;
}

void ALoot::CreateModifiers(UGameplayEffect*& Effect, int32 Number ) const
{
	Effect->Modifiers.SetNum(Number);

	for (FGameplayModifierInfo& Modifier : Effect->Modifiers)
	{
		Modifier.ModifierMagnitude = FScalableFloat();// attributre modifier value 
		Modifier.ModifierOp = EGameplayModOp::Additive;
		Modifier.Attribute = UGameAttributeSet::GetCurrentHealthAttribute(); //should find a way to get attribute
	}
	
}