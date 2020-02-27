// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameCharacter.h"
#include "GameBuilding.h"
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

public:

	UFUNCTION(BlueprintImplementableEvent)
		void DisplayCharacter(AGameCharacter* unit);

	UFUNCTION(BlueprintImplementableEvent)
		void DisplayBuilding(AGameBuilding* unit);

	UFUNCTION(BlueprintImplementableEvent)
		void DisplayNothing();

};


