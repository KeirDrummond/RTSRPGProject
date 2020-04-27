// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectAIController.h"
#include "CharacterAIController.h"
#include "ProjectGameMode.h"
#include "Engine/World.h"

AProjectAIController::AProjectAIController(){
	bWantsPlayerState = true;
}

void AProjectAIController::CommandMoveToLocation(AGameCharacter *unit, FVector location)
{
	ACharacterAIController* controller = Cast<ACharacterAIController>(unit->GetController());
	if (controller) { controller->MoveCommand(location); }

}

void AProjectAIController::CommandAttackMoveToLocation(AGameCharacter *unit, FVector location)
{
	if (IsValid(unit))
	{
		ACharacterAIController* controller = Cast<ACharacterAIController>(unit->GetController());
		if (controller) { controller->AttackMoveCommand(location); }
	}
}