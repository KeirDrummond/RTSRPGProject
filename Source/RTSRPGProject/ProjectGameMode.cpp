// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectGameMode.h"
#include "ProjectPlayerController.h"
#include "ProjectAIController.h"
#include "GamePlayerState.h"
#include "ProjectGameState.h"
#include "GameFramework/HUD.h"
#include "PlayerCamera.h"
#include "UObject/ConstructorHelpers.h"

AProjectGameMode::AProjectGameMode()
{
	PlayerControllerClass = AProjectPlayerController::StaticClass();
	DefaultPawnClass = NULL;
	PlayerStateClass = AGamePlayerState::StaticClass();
	GameStateClass = AProjectGameState::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHUDBPClass(TEXT("/Game/UserInterface/TheHUD"));
	if (PlayerHUDBPClass.Class != NULL)
	{
		HUDClass = PlayerHUDBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APawn> AIPlayerClass(TEXT("/Game/AI/AIPawn"));
	AIPlayer = AIPlayerClass.Class;
	
}

void AProjectGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) {
	Super::InitGame(MapName, Options, ErrorMessage);

	// Create players

	TSubclassOf<APawn> HumanPlayer = APlayerCamera::StaticClass();

	APawn* playerPawn = GetWorld()->SpawnActor<APawn>(HumanPlayer, FVector(0.f, 0.f, 0.f), FRotator::ZeroRotator);
	APawn* AIPawn = GetWorld()->SpawnActor<APawn>(AIPlayer, FVector(0.f, 0.f, 0.f), FRotator::ZeroRotator);
}