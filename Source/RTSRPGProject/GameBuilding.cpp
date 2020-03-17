// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBuilding.h"
#include "Engine/World.h"
#include "ProjectGameMode.h"

// Sets default values
AGameBuilding::AGameBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = mesh;
	spawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
	spawnPoint->AttachToComponent(mesh, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AGameBuilding::BeginPlay()
{
	Super::BeginPlay();

	AProjectGameMode* gamemode = Cast<AProjectGameMode>(GetWorld()->GetAuthGameMode());
	owningPlayer = gamemode->GetPlayer(0);
	
}

// Called every frame
void AGameBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGameBuilding::AddToQueue(TSoftClassPtr<AGameCharacter> unit) {

	return true;
}

void AGameBuilding::OnClick()
{
}

bool AGameBuilding::GetIsSelected()
{
	return selected;
}

AController* AGameBuilding::GetOwningPlayer()
{
	return owningPlayer;
}

void AGameBuilding::SetSelected(bool value)
{
	selected = value;
}

AGameCharacter* AGameBuilding::CreateUnit(TSubclassOf<AGameCharacter> unit) {
	FTransform transform = spawnPoint->GetComponentTransform();
	transform.SetScale3D(FVector(1, 1, 1));
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	return GetWorld()->SpawnActor<AGameCharacter>(unit, transform, params);
}