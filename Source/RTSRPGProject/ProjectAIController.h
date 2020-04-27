// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ProjectGameMode.h"
#include "GameFramework/Controller.h"
#include "GameCharacter.h"
#include "ProjectAIController.generated.h"

/**
 * 
 */
UCLASS()
class RTSRPGPROJECT_API AProjectAIController : public AAIController
{
	GENERATED_BODY()

public:

	AProjectAIController();

	UFUNCTION(BlueprintCallable)
		void CommandMoveToLocation(AGameCharacter *unit, FVector location);

	UFUNCTION(BlueprintCallable)
		void CommandAttackMoveToLocation(AGameCharacter *unit, FVector location);
};
