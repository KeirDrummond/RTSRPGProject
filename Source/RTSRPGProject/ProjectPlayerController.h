// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameHUD.h"
#include "GameCharacter.h"
#include "GameBuilding.h"
#include "ProjectGameMode.h"
#include "GameFramework/Controller.h"
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
	void SetNewAttackTarget(AActor* target);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	// When the shift button is pressed/released
	void OnShiftDown();
	void OnShiftUp();
	// When the left mouse button is pressed/released
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


	// Camera
	void MoveCamera();
	void ZoomCamera(float axisValue);

public:

	// Unit selection
	bool AddToSelected(IGameUnit* unit);
	bool RemoveFromSelected(IGameUnit* unit);
	bool RemoveAllFromSelected();
	void UnitsInBox(TArray<AActor*> units);
	// On selection, display unit data in the UI
	void UpdateDisplay();

	UFUNCTION(BlueprintCallable)
		void PauseGame();
	UFUNCTION(BlueprintCallable)
		void UnpauseGame();

};