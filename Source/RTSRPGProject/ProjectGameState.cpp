// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectGameState.h"
#include "GamePlayerState.h"
#include "ProjectGameMode.h"
#include "Engine/World.h"

void AProjectGameState::BeginPlay()
{
	PlayerArray[0]->SetPlayerName("Player 1");
	PlayerArray[1]->SetPlayerName("Player 2");
}

void AProjectGameState::PlayerDefeated(APlayerState* player)
{
	AGamePlayerState* ps = Cast<AGamePlayerState>(player);
	ps->alive = false;

	AProjectGameMode* gamemode = Cast<AProjectGameMode>(GetWorld()->GetAuthGameMode());
	gamemode->EndGame();
}