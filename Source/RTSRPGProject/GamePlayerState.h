// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GamePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class RTSRPGPROJECT_API AGamePlayerState : public APlayerState
{
	GENERATED_BODY()

public:

    // All of the data used by a player

    UPROPERTY(BlueprintReadOnly)
        TArray<AActor*> units;
    UPROPERTY(BlueprintReadOnly)
        TArray<AActor*> army;

    void AddToUnits(AActor* unit);

};
