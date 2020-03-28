// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBuilding.h"
#include "Engine/World.h"
#include "ProjectGameState.h"
#include "GamePlayerState.h"
#include "ProjectGameMode.h"

// Sets default values
AGameBuilding::AGameBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Creates a spawn point component in the building. Units will spawn at the spawn point rather than appear randomly around the building.
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = mesh;
	spawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
	spawnPoint->AttachToComponent(mesh, FAttachmentTransformRules::KeepRelativeTransform);

	defaultOwner = 0;
}

// Called when the game starts or when spawned
void AGameBuilding::BeginPlay()
{
	AProjectGameState* const gamestate = GetWorld()->GetGameState<AProjectGameState>();
	if (defaultOwner >= gamestate->PlayerArray.Num()) { defaultOwner = 0; }
	owningPlayer = gamestate->PlayerArray[defaultOwner];

	AGamePlayerState* op = Cast<AGamePlayerState>(owningPlayer);
	op->AddToUnits(this);

	Super::BeginPlay();
}

// Called every frame
void AGameBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AGameBuilding::IsInteractable()
{
	return interactable;
}

void AGameBuilding::SetOwningPlayer(APlayerState* player)
{
	owningPlayer = player;
}

bool AGameBuilding::GetIsSelected() { return selected; }

void AGameBuilding::SetSelected(bool value) { selected = value; }

APlayerState* AGameBuilding::GetOwningPlayer() { return owningPlayer; }

void AGameBuilding::TakeDamage(int32 damage)
{
}

// Spawns a unit
AGameCharacter* AGameBuilding::CreateUnit(TSubclassOf<AGameCharacter> unit) {
	FTransform transform = spawnPoint->GetComponentTransform();
	transform.SetScale3D(FVector(1, 1, 1));
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AGameCharacter* newUnit = GetWorld()->SpawnActor<AGameCharacter>(unit, transform, params);
	newUnit->SetOwningPlayer(owningPlayer);
	return newUnit;
}