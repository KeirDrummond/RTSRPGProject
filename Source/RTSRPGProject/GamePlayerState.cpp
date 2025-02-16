// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerState.h"
#include "GameCharacter.h"
#include "ProjectAIController.h"

AGamePlayerState::AGamePlayerState()
{
	resources = 0;
	resourceTimer = 5.f;
	alive = true;
}

void AGamePlayerState::AddToUnits(AActor* unit)
{
	units.Add(unit);
	AGameCharacter* armyUnit = Cast<AGameCharacter>(unit);
	if (armyUnit)
	{
		army.Add(armyUnit);

		if (IsValid(GetPawn())) {
			AProjectAIController* AIC = Cast<AProjectAIController>(GetPawn()->GetController());
			if (AIC) {
				AIC->NewUnit(armyUnit);
			}
		}
	}
	CalculateArmyPower();
}

void AGamePlayerState::RemoveFromUnits(AActor* unit)
{
	units.Remove(unit);
	AGameCharacter* armyUnit = Cast<AGameCharacter>(unit);
	if (armyUnit)
	{
		if (IsValid(GetPawn())) {
			AProjectAIController* AIC = Cast<AProjectAIController>(GetPawn()->GetController());
			if (AIC) {
				AIC->NewUnit(armyUnit);
			}
		}
		army.Remove(armyUnit);
	}
	CalculateArmyPower();
}

void AGamePlayerState::CalculateArmyPower()
{
	float power = 0;
	for (int i = 0; i < army.Num(); i++)
	{
		AGameCharacter *character = Cast<AGameCharacter>(army[i]);
		if (character)
		{
			power += character->basePower;
		}
	}
	ArmyPower = power;
}

bool AGamePlayerState::SpendResources(int cost) {
	if (resources < cost) { return false; }
	resources = resources - cost;

	return true;
}