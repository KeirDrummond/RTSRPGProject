// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameUnit.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class RTSRPGPROJECT_API AGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	AGameHUD();

protected:

	// Called on each frame update
	void DrawHUD() override;

public:

	// Remove the current widget display from the HUD
	UFUNCTION(BlueprintImplementableEvent)
		void DisplayNothing();

	// Creates the selection box to select multiple units at once
	void DrawBox();
	// If true, calls the DrawBox function
	bool drawBox;

	// The coordinates of opposite corners of the selection box
	FVector2D boxOrigin;
	FVector2D boxEnd;

private:

	// Actors found within the selection box
	TArray<AActor*> unitsFound;

};