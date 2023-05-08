// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "CustomAttributeHelper.generated.h"


UENUM(BlueprintType)
enum class ERarity : uint8 {
	RE_Common	 	UMETA(DisplayName = "Common"),
	RE_Rare		 	UMETA(DisplayName = "Rare"),
	RE_Legendary 	UMETA(DisplayName = "Legendary"),
};

UENUM(BlueprintType)
enum class EEquipmentType : uint8 {
	Chest	 	UMETA(DisplayName = "Chest"),
	Head	 	UMETA(DisplayName = "Head"),
	MainHand 	UMETA(DisplayName = "MainHand"),
	OffHand	 	UMETA(DisplayName = "OffHand"),
	Legs	 	UMETA(DisplayName = "Legs"),
	Ring	 	UMETA(DisplayName = "Ring"),
};

UENUM(BlueprintType) // not very good solution, but i don't see better ways
enum class EEquipmentAttributes : uint8 {
	Health 			UMETA(DisplayName = "Health"),
	Mana 			UMETA(DisplayName = "Mana"),
	HealthRegen	 	UMETA(DisplayName = "HealthRegen"),
	ManaRegen 		UMETA(DisplayName = "ManaRegen"),
	Defense	 		UMETA(DisplayName = "Defense"),
	AttackSpeed	 	UMETA(DisplayName = "AttackSpeed"),
	MovementSpeed 	UMETA(DisplayName = "MovementSpeed"),
};

USTRUCT(BlueprintType)
struct GAME_API FEquipmentData
{
	GENERATED_BODY()

public:

	FEquipmentData();

	FEquipmentData
	(FName Name, EEquipmentType EquipType, TMap<EEquipmentAttributes, float> MainAttributes,
	TMap<EEquipmentAttributes, float> SecondaryAttributes, ERarity Rarity, UStaticMesh* Appearance);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMesh* WorldAppearence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEquipmentType Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ERarity Rarity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<EEquipmentAttributes, float> MainAttributes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<EEquipmentAttributes, float> SecondaryAttributes;

		int32 GetAttributesNumber() const;// gives number of MainAttributes+SecondaryAttributes

		FORCEINLINE bool operator==(const FEquipmentData& Other) const {

			if (Name == Other.Name && Type == Other.Type && Rarity == Other.Rarity && WorldAppearence == Other.WorldAppearence) {
				return true;
			}
			else {
				return false;
			}
		}
};

UCLASS(Blueprintable)
class UCustomAttributeHelper : public UObject
{
	GENERATED_BODY()

public:
	UCustomAttributeHelper();

	//UFUNCTION(BlueprintCallable, Category = "Attributes")
		static FGameplayAttribute GetAttributeByName(const FName PropertyName);

	//UFUNCTION(BlueprintCallable, Category = "Attributes")
		static FGameplayAttribute GetAttributeByEnumName(const EEquipmentAttributes& PropertyEnum);

};

#if UE_BUILD_DEBUG
uint32 GetTypeHash(const FEquipmentData& Thing);
#else 
FORCEINLINE uint32 GetTypeHash(const FEquipmentData& Thing)
{
	uint32 Hash = FCrc::MemCrc32(&Thing, sizeof(FEquipmentData));
	return Hash;
}
#endif
