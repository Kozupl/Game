// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"

UCLASS()
class AGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGamePlayerController();

protected:
	/** True if the controlled character should navigate to the mouse cursor. 
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface
	UPROPERTY()
		APawn* PossessedPawn;

	virtual void OnPossess(APawn* InPawn);

	// Navigate player to the current mouse cursor location. 
	void MoveToMouseCursor();
	
	// Navigate player to the given world location. 
	void SetNewMoveDestination(const FVector DestLocation);

	// Input handlers for SetDestination action. 
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

//private:
	//bool IsImplementingHerpInterface;*/
};


