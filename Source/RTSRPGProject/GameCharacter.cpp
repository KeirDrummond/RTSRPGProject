// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"
#include "ProjectPlayerController.h"
#include "Engine.h"
#include "AIController.h"
#include "ProjectGameState.h"
#include "GameFramework/GameMode.h"
//#include "GenericPlatform/GenericPlatformMath.h"

// Sets default values
AGameCharacter::AGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	defaultOwner = 0;
}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	theAIController = Cast<AAIController>(GetController());

	AProjectGameState* const gamestate = GetWorld()->GetGameState<AProjectGameState>();
	owningPlayer = gamestate->PlayerArray[defaultOwner];

	if (maxHealth != NULL) { maxHealth = 1; }
	if (maxHealth < 1) { maxHealth = 1; }
	health = maxHealth;

	selected = false;

	Super::BeginPlay();
}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGameCharacter::MoveToPosition(const FVector target) {

	float const distance = FVector::Dist(target, GetActorLocation());

	if (distance > 120.0f) {
		theAIController->MoveToLocation(target);
	}
}

bool AGameCharacter::GetIsSelected()
{
	return selected;
}

APlayerState* AGameCharacter::GetOwningPlayer()
{
	return owningPlayer;
}

void AGameCharacter::SetSelected(bool value)
{
	selected = value;
}