// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectAIController.h"
#include "ProjectGameMode.h"
#include "Engine/World.h"

AProjectAIController::AProjectAIController(){
	bWantsPlayerState = true;
}

void AProjectAIController::LostUnit(AGameCharacter* unit)
{
	if (DefendingSquad.Find(unit))
	{
		DefendingSquad.Remove(unit);
	}
	else if (AttackingSquad.Find(unit))
	{
		AttackingSquad.Remove(unit);
	}
}

void AProjectAIController::CommandMoveSquadToLocation(TArray<AGameCharacter*> squad, FVector location)
{
	for (AGameCharacter* unit : squad)
	{
		unit->MoveCommand(location);
	}
}

void AProjectAIController::MoveToDefendingSquad(AGameCharacter* unit)
{
	if (AttackingSquad.Find(unit))
	{
		AttackingSquad.Remove(unit);
	}

	DefendingSquad.Add(unit);
}

void AProjectAIController::MoveToAttackingSquad(AGameCharacter* unit)
{
	if (DefendingSquad.Find(unit))
	{
		DefendingSquad.Remove(unit);
	}

	AttackingSquad.Add(unit);
}