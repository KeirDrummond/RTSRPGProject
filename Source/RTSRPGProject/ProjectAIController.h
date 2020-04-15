// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GamePlayer.h"
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

	void LostUnit(AGameCharacter* unit);
		
	UFUNCTION(BlueprintCallable)
		void CommandMoveSquadToLocation(TArray<AGameCharacter*> squad, FVector location);

	UPROPERTY(BlueprintReadOnly)
	TArray<AGameCharacter*> DefendingSquad;
	UPROPERTY(BlueprintReadOnly)
	TArray<AGameCharacter*> AttackingSquad;

	UFUNCTION(BlueprintCallable)
		void MoveToDefendingSquad(AGameCharacter* unit);
	UFUNCTION(BlueprintCallable)
		void MoveToAttackingSquad(AGameCharacter* unit);

};
