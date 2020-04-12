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

	void StartPlay() override;

	void Tick(float DeltaSeconds) override;

protected:

	float resourceTimer;

	// Reference spawn a new Human player
	TSubclassOf<APawn> HumanPlayer;
	// Reference spawn a new AI player
	TSubclassOf<APawn> AIPlayer;

public:

	UFUNCTION(BlueprintNativeEvent)
	void EndGame();

	virtual void EndGame_Implementation();

};
