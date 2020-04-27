// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GameCharacter.h"
#include "GamePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class RTSRPGPROJECT_API AGamePlayerState : public APlayerState
{
	GENERATED_BODY()

public:

    AGamePlayerState();

    // All of the data used by a player

    UPROPERTY(BlueprintReadOnly)
        TArray<AActor*> units;
    UPROPERTY(BlueprintReadOnly)
        TArray<AGameCharacter*> army;

    float resourceTimer;
    bool SpendResources(int value);

    UPROPERTY(BlueprintReadOnly)
        int resources;

    void AddToUnits(AActor* unit);
    void RemoveFromUnits(AActor* unit);

    UPROPERTY(BlueprintReadOnly)
        bool alive;

    UPROPERTY(BlueprintReadOnly)
        float ArmyPower;

    void CalculateArmyPower();

};
