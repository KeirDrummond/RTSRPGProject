// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionSystem.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameCharacter.h"

ACharacterAIController::ACharacterAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	sightConfig->SightRadius = 500;
	sightConfig->LoseSightRadius = 500;
	sightConfig->PeripheralVisionAngleDegrees = 180.f;
	sightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	sightConfig->DetectionByAffiliation.bDetectEnemies = true;
	sightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	aiPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component"));
	aiPerceptionComponent->ConfigureSense(*sightConfig);
	aiPerceptionComponent->SetDominantSense(sightConfig->GetSenseImplementation());
	UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, sightConfig->GetSenseImplementation(), GetPawn());
	
	currentCommand = ECommandsEnum::CE_Idle;

	PrimaryActorTick.bCanEverTick = true;
}

void ACharacterAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacterAIController::Tick(float DeltaSeconds)
{
	DoCommand();
	
	Super::Tick(DeltaSeconds);
}

bool ACharacterAIController::MoveToPosition(const FVector target) {

	AGameCharacter *myPawn =  Cast<AGameCharacter>(GetPawn());
	if (!myPawn->alive) { return false; }

	myPawn->SetState(EUnitStateEnum::CE_Movement);

	FRotator rotation = UKismetMathLibrary::FindLookAtRotation(myPawn->GetActorLocation(), target);
	rotation.Pitch = 0.f;
	rotation.Roll = 0.f;
	myPawn->SetActorRotation(rotation);

	MoveToLocation(
		target,
		50.f,
		true,
		true,
		false,
		true,
		0,
		true);

	return true;
}

void ACharacterAIController::DoCommand()
{
	if (currentCommand == ECommandsEnum::CE_Idle)
	{
		DoIdle();
	}
	else if (currentCommand == ECommandsEnum::CE_Movement)
	{
		if (GetMoveStatus() == EPathFollowingStatus::Idle)
		{
			Idle();
		}
	}
	else if (currentCommand == ECommandsEnum::CE_Attack)
	{
		AttackCommand(currentTarget);
	}
	else if (currentCommand == ECommandsEnum::CE_AttackMove)
	{
		DoAttackMove(currentDestination);
	}
}

bool ACharacterAIController::Idle() {

	if (GetPawn() == nullptr) { return false; }
	AGameCharacter* myPawn = Cast<AGameCharacter>(GetPawn());
	if (!myPawn->alive) { return false; }

	currentCommand = ECommandsEnum::CE_Idle;
	myPawn->SetState(EUnitStateEnum::CE_Idle);
	StopMovement();
	currentDestination = GetPawn()->GetActorLocation();

	return true;
}

bool ACharacterAIController::DoIdle()
{
	AGameCharacter* myPawn = Cast<AGameCharacter>(GetPawn());
	TArray<AActor*> units = GetPerception();

	if (units.Num() != 0 && currentTarget == nullptr)
	{
		currentTarget = units[0];
	}
	
	if (currentTarget != nullptr)
	{
		if (!myPawn->AttackTarget(currentTarget))
		{
			currentTarget = nullptr;
		}
	}

	return true;
}

bool ACharacterAIController::MoveCommand(const FVector destination)
{
	if (GetPawn() == nullptr) { return false; }
	AGameCharacter* myPawn = Cast<AGameCharacter>(GetPawn());
	if (!myPawn->alive) { return false; }

	currentTarget = nullptr;
	currentCommand = ECommandsEnum::CE_Movement;
	currentDestination = destination;
	MoveToPosition(destination);

	return true;
}

bool ACharacterAIController::AttackCommand(AActor* target)
{
	if (GetPawn() == nullptr) { return false; }
	AGameCharacter* myPawn = Cast<AGameCharacter>(GetPawn());
	if (!myPawn->alive) { return false; }

	if (!IsValid(target)) {
		Idle();
		return false;
	}

	if (target->GetClass()->ImplementsInterface(UGameUnit::StaticClass()))
	{
		IGameUnit* unit = Cast<IGameUnit>(target);
		if (!unit->IsAlive())
		{
			Idle();
			return false;
		}
	}

	currentTarget = target;
	currentCommand = ECommandsEnum::CE_Attack;

	if (!myPawn->AttackTarget(target))
	{
		FVector targetPos = target->GetActorLocation();
		MoveToLocation(targetPos);
		currentDestination = targetPos;
	}

	return true;
}

bool ACharacterAIController::AttackMoveCommand(const FVector destination)
{
	if (GetPawn() == nullptr) { return false; }
	AGameCharacter* myPawn = Cast<AGameCharacter>(GetPawn());
	if (!myPawn->alive) { return false; }

	currentCommand = ECommandsEnum::CE_AttackMove;
	currentDestination = destination;

	MoveToPosition(destination);

	return true;
}

bool ACharacterAIController::DoAttackMove(const FVector destination)
{
	AGameCharacter* myPawn = Cast<AGameCharacter>(GetPawn());

	FVector myPos = myPawn->GetActorLocation();
	float distance = FVector::Distance(myPos, destination);

	TArray<AActor*> units = GetPerception();

	if (units.Num() != 0 && currentTarget == nullptr)
	{
		currentTarget = units[0];
	}

	if (currentTarget != nullptr)
	{
		if (myPawn->AttackTarget(currentTarget))
		{
			return true;
		}
		else
		{
			currentTarget = nullptr;
		}
	}

	if (distance > 50.f)
	{
		MoveToPosition(destination);
	}
	else
	{
		Idle();
	}

	return true;
}

TArray<AActor*> ACharacterAIController::GetPerception()
{
	TArray<AActor*> actors;
	aiPerceptionComponent->GetCurrentlyPerceivedActors(GetAIPerceptionComponent()->GetDominantSense(), actors);

	TArray<AActor*> units;

	for (AActor* actor : actors)
	{
		if (actor->GetClass()->ImplementsInterface(UGameUnit::StaticClass()))
		{
			IGameUnit* unit = Cast<IGameUnit>(actor);
			AGameCharacter* myPawn = Cast<AGameCharacter>(GetPawn());
			if (unit->GetOwningPlayer() != myPawn->GetOwningPlayer() && unit->IsAlive()) { units.AddUnique(actor); }			
		}
	}

	return units;
}
