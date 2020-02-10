// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBuilding.h"

// Sets default values
AGameBuilding::AGameBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameBuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGameBuilding::CreateUnit(AGameCharacter* unit) {
	if (!IsValid(unit)) { return false; }

	return true;
}