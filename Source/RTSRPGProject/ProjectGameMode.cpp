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

	//static ConstructorHelpers::FClassFinder<APawn> HumanPlayerClass(TEXT("/Game/Player/PlayerPawn"));
	//HumanPlayer = HumanPlayerClass.Class;
	static ConstructorHelpers::FClassFinder<APawn> AIPlayerClass(TEXT("/Game/AI/AIPawn"));
	AIPlayer = AIPlayerClass.Class;
	
	PrimaryActorTick.bCanEverTick = true;
	resourceTimer = 5.f;
}

void AProjectGameMode::StartPlay() {
	// Create players
	HumanPlayer = APlayerCamera::StaticClass();
	APawn* playerPawn = GetWorld()->SpawnActor<APawn>(HumanPlayer, FVector(0.f, 0.f, 0.f), FRotator::ZeroRotator);
	APawn* AIPawn = GetWorld()->SpawnActor<APawn>(AIPlayer, FVector(0.f, 0.f, 0.f), FRotator::ZeroRotator);

	// Run Begin Play for all other actors
	Super::StartPlay();
}

void AProjectGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	resourceTimer = resourceTimer - DeltaSeconds;
	if (resourceTimer < 0.f)
	{
		for (APlayerState* ps : GameState->PlayerArray)
		{
			AGamePlayerState* playerState = Cast<AGamePlayerState>(ps);
			playerState->resources += 10;
			resourceTimer = 5.f;
		}
	}	
}

void AProjectGameMode::EndGame_Implementation() {
	AGamePlayerState* player1State = Cast<AGamePlayerState>(GameState->PlayerArray[0]);
	AProjectPlayerController* pc = Cast<AProjectPlayerController>(player1State->GetPawn()->GetController());
	pc->PauseGame();
	// Widget called in blueprint
}