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

protected:

	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	// Reference spawn a new AI player
	TSubclassOf<APawn> AIPlayer;

};
