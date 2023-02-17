// Copyright Epic Games, Inc. All Rights Reserved.

#include "GamePlayerController.h"

AGamePlayerController::AGamePlayerController()
{
	SetShowMouseCursor(true);
	//IsImplementingHerpInterface = false;
}
/*
void AGamePlayerController::OnPossess(APawn* InPawn)
{
	PossessedPawn = InPawn;
	/*if (PossessedPawn->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
	{
		IsImplementingHerpInterface = true;
	}*/
/*}

void AGamePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void AGamePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AGamePlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AGamePlayerController::OnSetDestinationReleased);
}

void AGamePlayerController::MoveToMouseCursor()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	if (Hit.bBlockingHit)
	{
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void AGamePlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	if (PossessedPawn)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
	}
}

void AGamePlayerController::OnSetDestinationPressed()
{
	//Interface* InterfaceName = Cast<Interface>(Actor);
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	if (Hit.GetActor()->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()) /* && IsImplementingHerpInterface)
	{
		ICharacters_Interface::Execute_AttackTarget(PossessedPawn, Hit.GetActor()->GetAbilitySystemComponent());
	}
	else if (Hit.bBlockingHit)
	{
		bMoveToMouseCursor = true;
	}
}

void AGamePlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}*/
