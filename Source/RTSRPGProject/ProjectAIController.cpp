// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectAIController.h"
#include "CharacterAIController.h"
#include "ProjectGameMode.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

AProjectAIController::AProjectAIController(){
	bWantsPlayerState = true;
}

void AProjectAIController::NewUnit(AGameCharacter* unit) {
	AddToReserveSquad(unit);
}

void AProjectAIController::LostUnit(AGameCharacter* unit)
{
	for (FSquad squad : squads) {
		squad.units.Remove(unit);
	}
}

void AProjectAIController::CommandMoveToLocation(AGameCharacter *unit, FVector location) {
	if (IsValid(unit)) {
		ACharacterAIController* controller = Cast<ACharacterAIController>(unit->GetController());
		if (controller) { controller->MoveCommand(location); }
	}
}

void AProjectAIController::CommandAttackMoveToLocation(AGameCharacter *unit, FVector location) {
	if (IsValid(unit))
	{
		ACharacterAIController* controller = Cast<ACharacterAIController>(unit->GetController());
		if (controller) { controller->AttackMoveCommand(location); }
	}
}

void AProjectAIController::AddToReserveSquad(AGameCharacter* unit)
{
	if (IsValid(unit))
	{
		bool found = false;
		for (int32 i = 0; i < squads.Num(); i++) {
			if (squads[i].wantedState == SquadState::Reserve)
			{
				found = true;
				AddToSquad(unit, i);
				break;
			}
		}
		if (!found)
		{
			FSquad newSquad = FSquad();
			int32 index = squads.Add(newSquad);
			AddToSquad(unit, index);
		}
	}
}

void AProjectAIController::AddToSquad(AGameCharacter* unit, int32 index)
{
	if (IsValid(unit)) {
		squads[index].units.Add(unit);
		squads[index].power += unit->basePower;
	}
}

void AProjectAIController::RemoveFromSquad(AGameCharacter* unit, int32 index)
{
	if (IsValid(unit)) {
		squads[index].units.Remove(unit);
		squads[index].power -= unit->basePower;
	}
}
