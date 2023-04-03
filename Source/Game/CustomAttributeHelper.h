// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"
#include "CustomAttributeHelper.generated.h"


UENUM(BlueprintType)
enum class ERarity : uint8 {
	RE_Common     UMETA(DisplayName = "Common"),
	RE_Rare       UMETA(DisplayName = "Rare"),
	RE_Legendary  UMETA(DisplayName = "Legendary"),
};

//it will be better to make enum for stats, instead of FName

USTRUCT(BlueprintType)
struct GAME_API FEquipmentData
{
	GENERATED_BODY()

public:

	FEquipmentData();
	FEquipmentData
	(FName Name, FName TypetagName, TMap<FName, float> MainAttributes,
	TMap<FName, float> SecondaryAttributes, ERarity Rarity, UStaticMesh* Appearance);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMesh* Appearance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGameplayTag Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ERarity Rarity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<FName, float> MainAttributes;//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<FName, float> SecondaryAttributes;//

		int32 GetAttributesNumber() const;// gives number of MainAttributes+SecondaryAttributes
};

UCLASS(Blueprintable)
class UCustomAttributeHelper : public UObject
{
	GENERATED_BODY()

public:
	UCustomAttributeHelper();

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		static FGameplayAttribute GetAttributeByName(FName PropertyName); //FGameplayAttribute* pointer is impossible
};

USTRUCT(BlueprintType)
struct GAME_API FRandomLoot
{
	GENERATED_BODY()

public:

	FRandomLoot();
	FRandomLoot(FName TypeTagName, ERarity Rarity, int32 level);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGameplayTag Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ERarity Rarity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Level;

	FORCEINLINE bool operator==(const FRandomLoot& Other) const {

		if (Rarity == Other.Rarity && Level == Other.Level && Type == Other.Type) {
			return true;
		}
		else {
			return false;
		}
	}

};

#if UE_BUILD_DEBUG
uint32 GetTypeHash(const FRandomLoot& Thing);
#else // optimize by inlining in shipping and development builds (what???)
FORCEINLINE uint32 GetTypeHash(const FRandomLoot& Thing)
{
	uint32 Hash = FCrc::MemCrc32(&Thing, sizeof(FRandomLoot));
	return Hash;
}
#endif