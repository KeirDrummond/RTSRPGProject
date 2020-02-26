// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectPlayerController.h"
#include "PlayerCamera.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "RTSRPGProjectCharacter.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

AProjectPlayerController::AProjectPlayerController()
{
	bShowMouseCursor = true;
	//DefaultMouseCursor = EMouseCursor::Crosshairs;
	bEnableClickEvents = true;
}

void AProjectPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void AProjectPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	//APlayerCamera* playerCamera = Cast<APlayerCamera>(GetPawn());

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AProjectPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AProjectPlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("Selection", IE_Pressed, this, &AProjectPlayerController::OnClick);

	InputComponent->BindAction("Shift", IE_Pressed, this, &AProjectPlayerController::OnShiftDown);
	InputComponent->BindAction("Shift", IE_Released, this, &AProjectPlayerController::OnShiftUp);
}

void AProjectPlayerController::MoveToMouseCursor()
{
	//Movement command functionality

	/*
	if (ARTSRPGProjectCharacter* MyPawn = Cast<ARTSRPGProjectCharacter>(GetPawn()))
	{
		if (MyPawn->GetCursorToWorld())
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
		}
	}*/

	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void AProjectPlayerController::OnClick() {
	FHitResult hit;
	GetHitResultUnderCursor(ECC_Visibility, false, hit);

	if (!shiftDown) { RemoveAllFromSelected(); }

	IGameUnit* hitUnit = Cast<IGameUnit>(hit.GetActor());
	if (hitUnit) { AddToSelected(hitUnit); }
}

void AProjectPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	if (unitArray.Num() != 0)
	for (int32 i = 0; i <= unitArray.Num() - 1; i++)
	{
		AGameCharacter* unit = Cast<AGameCharacter>(unitArray[i]);
		if (IsValid(unit)) { unit->MoveToPosition(DestLocation); }
	}

}

void AProjectPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AProjectPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void AProjectPlayerController::OnShiftDown()
{
	shiftDown = true;
}

void AProjectPlayerController::OnShiftUp()
{
	shiftDown = false;
}

bool AProjectPlayerController::AddToSelected(IGameUnit* unit)
{
	UObject* theUnit = unit->_getUObject();
	if (!theUnit->GetClass()->ImplementsInterface(UGameUnit::StaticClass())) { return false; }

	if (!shiftDown) { RemoveAllFromSelected(); }

	AGameCharacter* character = Cast<AGameCharacter>(unit);
	if (character) { unitArray.Add(unit); character->SetSelected(true); }
	AGameBuilding* building = Cast<AGameBuilding>(unit);
	if (building) { building->SetSelected(true); }

	IGameUnit::Execute_UpdateColour(theUnit);

	return true;
}

bool AProjectPlayerController::RemoveFromSelected(IGameUnit* unit)
{
	UObject* theUnit = unit->_getUObject();
	if (!unit->_getUObject()->GetClass()->ImplementsInterface(UGameUnit::StaticClass())) { return false; }

	AGameCharacter* character = Cast<AGameCharacter>(unit);
	if (character) { unitArray.Remove(character); character->SetSelected(false); }
	AGameBuilding* building = Cast<AGameBuilding>(unit);
	if (building) { building->SetSelected(false); }

	IGameUnit::Execute_UpdateColour(theUnit);

	return true;
}

bool AProjectPlayerController::RemoveAllFromSelected()
{
	for (int32 i = unitArray.Num() - 1; i >= 0; i--) { 
		RemoveFromSelected(unitArray[i]); }
	unitArray.Empty();

	return true;
}
