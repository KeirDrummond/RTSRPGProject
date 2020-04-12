// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerState.h"
#include "GameCharacter.h"

AGamePlayerState::AGamePlayerState()
{
	resources = 0;
	resourceTimer = 5.f;
}

void AGamePlayerState::AddToUnits(AActor* unit)
{
	units.Add(unit);
	AGameCharacter* armyUnit = Cast<AGameCharacter>(unit);
	if (armyUnit)
	{
		army.Add(armyUnit);
	}
}

bool AGamePlayerState::SpendResources(int cost) {
	if (resources < cost) { return false; }
	resources = resources - cost;

	return true;
}