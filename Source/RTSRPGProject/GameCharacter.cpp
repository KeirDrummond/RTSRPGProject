// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"
#include "ProjectPlayerController.h"
#include "Engine.h"
#include "AIController.h"
#include "ProjectGameState.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/GameMode.h"

// Sets default values
AGameCharacter::AGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	defaultOwner = 0;
	interactable = true;
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

	if (maxHealth <= 0) { maxHealth = 1; }
	if (maxHealth < 1) { maxHealth = 1; }
	health = maxHealth;

	selected = false;

	Super::BeginPlay();
}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	DoCommand();
	attackCooldown = FGenericPlatformMath::Max(attackCooldown - DeltaTime, 0.f);
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

bool AGameCharacter::IsInteractable()
{
	return interactable;
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
	UpdateAnimation(ECommandsEnum::CE_Idle);
	theAIController->StopMovement();
}

void AGameCharacter::MoveCommand(const FVector destination)
{
	currentCommand = ECommandsEnum::CE_Movement;
	UpdateAnimation(ECommandsEnum::CE_Movement);
	currentDestination = destination;
	MoveToPosition(destination);
}

bool AGameCharacter::AttackCommand(AActor* target)
{
	if (!IsValid(target)) {
		Idle();
		return false;
	}

	if (target->GetClass()->ImplementsInterface(UGameUnit::StaticClass()))
	{
		IGameUnit* unit = Cast<IGameUnit>(target);
		if (!unit->IsInteractable())
		{
			Idle();
			return false;
		}
	}

	currentTarget = target;
	currentCommand = ECommandsEnum::CE_Attack;

	FVector myPos = this->GetActorLocation();
	FVector targetPos = target->GetActorLocation();
	
	float distance = FVector::Distance(myPos, targetPos);

	if (distance < attackRange)
	{
		theAIController->StopMovement();
		AttackTarget(target);
		UpdateAnimation(ECommandsEnum::CE_Attack);
		const FRotator rotation = UKismetMathLibrary::FindLookAtRotation(myPos, targetPos);
		SetActorRotation(rotation);
	}
	else
	{
		UpdateAnimation(ECommandsEnum::CE_Movement);
		theAIController->MoveToLocation(targetPos);
		currentDestination = targetPos;
	}

	return true;
}

void AGameCharacter::AttackTarget(AActor* target)
{
	UpdateAnimation(currentCommand);
	if (attackCooldown <= 0)
	{
		if (target->GetClass()->ImplementsInterface(UGameUnit::StaticClass()))
		{
			IGameUnit* unit = Cast<IGameUnit>(target);
			unit->TakeDamage(attack);
			attackCooldown = 1;
		}
	}
}

void AGameCharacter::TakeDamage(int32 damage)
{
	health = health - damage;
	UpdateHealth();
}