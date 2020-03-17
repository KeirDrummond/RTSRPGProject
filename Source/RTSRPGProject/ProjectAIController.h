// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GamePlayer.h"
#include "ProjectGameMode.h"
#include "GameFramework/Controller.h"
#include "ProjectAIController.generated.h"

/**
 * 
 */
UCLASS()
class RTSRPGPROJECT_API AProjectAIController : public AAIController, public IGamePlayer
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	
};
