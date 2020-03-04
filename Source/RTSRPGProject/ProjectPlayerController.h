// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameHUD.h"
#include "GameCharacter.h"
#include "GameBuilding.h"
#include "ProjectPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RTSRPGPROJECT_API AProjectPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AProjectPlayerController();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;
	uint32 shiftDown : 1;
	uint32 drawingBox : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	void OnShiftDown();
	void OnShiftUp();

	void OnClickPressed();
	void OnClickReleased();

	FVector2D GetCursorPosition();

private:

	TArray<IGameUnit*> unitArray;

	IGameUnit* displayedUnit;

	AGameHUD* theHUD;

	FVector2D boxOrigin;
	FVector2D boxEnd;
	TArray<AActor*> unitsFound;

public:

	bool AddToSelected(IGameUnit* unit);
	bool RemoveFromSelected(IGameUnit* unit);
	bool RemoveAllFromSelected();

	void UnitsInBox(TArray<AActor*> units);

	void UpdateDisplay();

};