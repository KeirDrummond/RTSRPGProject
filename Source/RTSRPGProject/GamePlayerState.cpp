// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerState.h"
#include "GameCharacter.h"

void AGamePlayerState::AddToUnits(AActor* unit)
{
	units.Add(unit);
	AGameCharacter* armyUnit = Cast<AGameCharacter>(unit);
	if (armyUnit)
	{
		army.Add(armyUnit);
	}
}