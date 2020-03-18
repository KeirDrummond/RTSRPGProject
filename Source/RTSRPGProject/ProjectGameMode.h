// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamePlayer.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectGameMode.generated.h"

/**
 * 
 */
UCLASS()
class RTSRPGPROJECT_API AProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AProjectGameMode();

	// Tracks players in the game and distributes them on request
	UFUNCTION(BlueprintPure)
	TArray<AController*> GetPlayerList();
	AController* GetPlayer(int value);

protected:

	virtual void BeginPlay() override;

	// Reference spawn a new AI player
	TSubclassOf<APawn> AIPlayer;
	// The Player list
	TArray<AController*> playerList;

};
