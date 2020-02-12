// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"
#include "ProjectPlayerController.h"
#include "Engine.h"
#include "AIController.h"
//#include "GenericPlatform/GenericPlatformMath.h"

// Sets default values
AGameCharacter::AGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	playerController = Cast<AProjectPlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	theAIController = Cast<AAIController>(GetController());

	if (maxHealth != NULL) { maxHealth = 1; }
	if (maxHealth < 1) { maxHealth = 1; }
	health = maxHealth;
	
	selected = false;
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

bool AGameCharacter::AddToSelected() {
	if (!IsValid(playerController)) { return false; }
	return playerController->AddToSelected(this);
}

bool AGameCharacter::RemoveFromSelected() {
	if (!IsValid(playerController)) { return false; }
	return playerController->RemoveFromSelected(this);
}

void AGameCharacter::MoveToPosition(const FVector target) {

	float const distance = FVector::Dist(target, GetActorLocation());

	if (distance > 120.0f) {
		theAIController->MoveToLocation(target);
	}
}