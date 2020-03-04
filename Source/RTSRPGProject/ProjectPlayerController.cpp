// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectPlayerController.h"
#include "PlayerCamera.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "RTSRPGProjectCharacter.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "GameHUD.h"

AProjectPlayerController::AProjectPlayerController()
{
	bShowMouseCursor = true;
	//DefaultMouseCursor = EMouseCursor::Crosshairs;
	bEnableClickEvents = true;
}

void AProjectPlayerController::BeginPlay()
{
	theHUD = Cast<AGameHUD>(MyHUD);
}

void AProjectPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}

	if (drawingBox)
	{
		theHUD->boxEnd = GetCursorPosition();
		theHUD->drawBox = true;
	}
	else { theHUD->drawBox = false; }

}

void AProjectPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	//APlayerCamera* playerCamera = Cast<APlayerCamera>(GetPawn());

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AProjectPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AProjectPlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("Selection", IE_Pressed, this, &AProjectPlayerController::OnClickPressed);
	InputComponent->BindAction("Selection", IE_Released, this, &AProjectPlayerController::OnClickReleased);

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

void AProjectPlayerController::OnClickPressed() {

	theHUD->boxOrigin = GetCursorPosition();
	boxOrigin = GetCursorPosition();
	drawingBox = true;
}

void AProjectPlayerController::OnClickReleased() {
	drawingBox = false;
	boxEnd = GetCursorPosition();

	if (FVector2D::Distance(boxOrigin, boxEnd) < 1.0f) {
		FHitResult hit;
		GetHitResultUnderCursor(ECC_Visibility, false, hit);

		if (!shiftDown) { RemoveAllFromSelected(); }

		IGameUnit* hitUnit = Cast<IGameUnit>(hit.GetActor());
		if (hitUnit) { AddToSelected(hitUnit); }
	}
	else
	{
		if (!shiftDown) { RemoveAllFromSelected(); }

		if (unitsFound.Num() > 0) {
			for (AActor* unit : unitsFound) {
				IGameUnit* theUnit = Cast<IGameUnit>(unit);
				if (theUnit) { AddToSelected(theUnit); }
			}
		}
	}

	UpdateDisplay();
}

FVector2D AProjectPlayerController::GetCursorPosition() {
	float x;
	float y;
	GetMousePosition(x, y);
	
	return FVector2D(x, y);
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

	AGameCharacter* character = Cast<AGameCharacter>(unit);
	if (character) { character->SetSelected(true); }
	AGameBuilding* building = Cast<AGameBuilding>(unit);
	if (building) { building->SetSelected(true); }

	unitArray.Add(unit);

	IGameUnit::Execute_UpdateColour(theUnit);

	return true;
}

bool AProjectPlayerController::RemoveFromSelected(IGameUnit* unit)
{
	UObject* theUnit = unit->_getUObject();
	if (!unit->_getUObject()->GetClass()->ImplementsInterface(UGameUnit::StaticClass())) { return false; }

	AGameCharacter* character = Cast<AGameCharacter>(unit);
	if (character) { character->SetSelected(false); }
	AGameBuilding* building = Cast<AGameBuilding>(unit);
	if (building) { building->SetSelected(false); }

	unitArray.Remove(unit);

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

void AProjectPlayerController::UnitsInBox(TArray<AActor*> units)
{
	unitsFound.Empty();
	unitsFound = units;
}

void AProjectPlayerController::UpdateDisplay()
{
	if (unitArray.Num() != 0) {
		displayedUnit = unitArray[0];
		for (IGameUnit* unit : unitArray)
		{
			if (Cast<AGameBuilding>(unit->_getUObject())) { displayedUnit = unit; break; }
		}
	}
	else { displayedUnit = NULL; theHUD->DisplayNothing(); }

	if (displayedUnit != NULL)
	{
		if (displayedUnit->_getUObject()->GetClass()->ImplementsInterface(UGameUnit::StaticClass()))
		{
			IGameUnit::Execute_OnDisplay(displayedUnit->_getUObject());
		}
	}

}
