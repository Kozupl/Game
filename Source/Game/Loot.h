// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class UGameplayEffect* CreateGA(FName Name) const;

	void CreateModifiers(class UGameplayEffect*& Effect, int32 Number) const;// only use for instanced GA

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float AttackPower = 10.f;

	void Equip(class UAbilitySystemComponent* EquiperASC) const;

};
