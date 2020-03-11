// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBuilding.h"
#include "Engine/World.h"

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

void AGameBuilding::SetSelected(bool value)
{
	selected = value;
}

int8 AGameBuilding::GetOwningPlayer()
{
	return (int8)owningPlayer;
}

AGameCharacter* AGameBuilding::CreateUnit(TSubclassOf<AGameCharacter> unit) {
	FTransform transform = spawnPoint->GetComponentTransform();
	transform.SetScale3D(FVector(1, 1, 1));
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	return GetWorld()->SpawnActor<AGameCharacter>(unit, transform, params);
}