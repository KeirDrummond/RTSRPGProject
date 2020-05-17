// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"
#include "ProjectPlayerController.h"
#include "ProjectAIController.h"
#include "Engine.h"
#include "AIController.h"
#include "ProjectGameState.h"
#include "GamePlayerState.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/GameMode.h"

// Sets default values
AGameCharacter::AGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	defaultOwner = 0;
	alive = true;
	currentState = EUnitStateEnum::CE_Idle;
}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	theAIController = Cast<AAIController>(GetController());

	AProjectGameState* const gamestate = GetWorld()->GetGameState<AProjectGameState>();
	if (defaultOwner >= gamestate->PlayerArray.Num()) { defaultOwner = 0; }
	if (owningPlayer == NULL)
	{
		owningPlayer = gamestate->PlayerArray[defaultOwner];
	}	

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
	attackCooldown = FGenericPlatformMath::Max(attackCooldown - DeltaTime, 0.f);

	Super::Tick(DeltaTime);
}

void AGameCharacter::SetOwningPlayer(APlayerState* player)
{
	owningPlayer = player;
}

bool AGameCharacter::GetIsSelected()
{
	return selected;
}

bool AGameCharacter::IsAlive()
{
	return alive;
}

APlayerState* AGameCharacter::GetOwningPlayer()
{
	return owningPlayer;
}

void AGameCharacter::SetSelected(bool value)
{
	selected = value;
}

bool AGameCharacter::AttackTarget(AActor *target)
{
	if (!alive) { return false; }

	if (!target->GetClass()->ImplementsInterface(UGameUnit::StaticClass())) { return false; }
	IGameUnit* unit = Cast<IGameUnit>(target);
	if (!unit->IsAlive()) { return false; }

	FVector myPos = GetActorLocation();
	FVector targetPos = target->GetActorLocation();

	float distance = FVector::Distance(myPos, targetPos);

	if (distance < attackRange)
	{
		if (attackCooldown <= 0)
		{
			
			unit->TakeDamage(attack);
			attackCooldown = 1;
		}

		SetState(EUnitStateEnum::CE_Attack);
		GetController()->StopMovement();
		FRotator rotation = UKismetMathLibrary::FindLookAtRotation(myPos, targetPos);
		rotation.Pitch = 0.f;
		rotation.Roll = 0.f;
		SetActorRotation(rotation);
		return true;
	}

	SetState(EUnitStateEnum::CE_Idle);
	return false;
}

void AGameCharacter::SetState(EUnitStateEnum state)
{
	currentState = state;
	SetStateBP(state);
}

void AGameCharacter::TakeDamage(int32 damage)
{
	health -= damage;
	UpdateHealth();
	if (health <= 0)
	{
		OnDeath();
	}
}

void AGameCharacter::OnDeath()
{
	alive = false;
	GetController()->StopMovement();

	SetState(EUnitStateEnum::CE_Dead);
	SetLifeSpan(5.f);
	GetCapsuleComponent()->SetCollisionProfileName("IgnoreOnlyPawn");

	AGamePlayerState* op = Cast<AGamePlayerState>(owningPlayer);
	op->RemoveFromUnits(this);

	AProjectPlayerController* humanPlayer = Cast<AProjectPlayerController>(owningPlayer->GetPawn()->GetController());
	if (humanPlayer)
	{
		humanPlayer->RemoveFromSelected(this);
	}

	OnDeathBP();
}