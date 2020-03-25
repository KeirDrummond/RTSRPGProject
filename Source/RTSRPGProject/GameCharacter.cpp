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
	currentCommand = ECommandsEnum::CE_Idle;
}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	theAIController = Cast<AAIController>(GetController());

	AProjectGameState* const gamestate = GetWorld()->GetGameState<AProjectGameState>();
	if (defaultOwner >= gamestate->PlayerArray.Num()) { defaultOwner = 0; }
	owningPlayer = gamestate->PlayerArray[defaultOwner];

	AGamePlayerState* op = Cast<AGamePlayerState>(owningPlayer);
	op->AddToUnits(this);

	if (maxHealth != NULL) { maxHealth = 1; }
	if (maxHealth < 1) { maxHealth = 1; }
	health = maxHealth;

	selected = false;

	Super::BeginPlay();
}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	DoCommand();
	Super::Tick(DeltaTime);
}

void AGameCharacter::SetOwningPlayer(APlayerState* player)
{
	owningPlayer = player;
}

void AGameCharacter::MoveToPosition(const FVector target) {
	theAIController->MoveToLocation(target);
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

// Commands. How the game character knows what it is supposed to do.

void AGameCharacter::DoCommand()
{
	if (currentCommand == ECommandsEnum::CE_Movement)
	{
		float const distance = FVector::Dist(currentDestination, GetActorLocation());
		if (distance < 120.0f) {
			// Upon arriving to the destination, become idle.
			Idle();
		}
	}
	else if (currentCommand == ECommandsEnum::CE_Attack)
	{
		// Repeats the attack command with new data.
		AttackCommand(currentTarget);
	}
}

void AGameCharacter::Idle() {
	currentCommand = ECommandsEnum::CE_Idle;
	theAIController->StopMovement();
}

void AGameCharacter::MoveCommand(const FVector destination)
{
	currentCommand = ECommandsEnum::CE_Movement;
	currentDestination = destination;
	MoveToPosition(destination);
}

bool AGameCharacter::AttackCommand(AActor* target)
{
	if (!IsValid(target)) {
		Idle();
		return false;
	}

	FVector myPos = this->GetActorLocation();
	FVector targetPos = target->GetActorLocation();
	
	if (FVector::Distance(myPos, targetPos) < attackRange)
	{
		theAIController->StopMovement();
		AttackTarget(target);
	}
	else
	{
		MoveToPosition(targetPos);
	}

	return true;
}

void AGameCharacter::AttackTarget(AActor* target)
{
	if (attackCooldown <= 0)
	{
		if (target->GetClass()->ImplementsInterface(UGameUnit::StaticClass()))
		{
			IGameUnit* unit = Cast<IGameUnit>(target);
			unit->TakeDamage(attack);
		}
	}
}

void AGameCharacter::TakeDamage(int32 damage)
{
	health = health - damage;
}