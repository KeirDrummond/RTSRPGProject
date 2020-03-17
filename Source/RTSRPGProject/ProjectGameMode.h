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

	UFUNCTION(BlueprintPure)
	TArray<AController*> GetPlayerList();
	AController* GetPlayer(int value);

protected:

	virtual void BeginPlay() override;

	TSubclassOf<APawn> AIPlayer;
	TArray<AController*> playerList;

};
