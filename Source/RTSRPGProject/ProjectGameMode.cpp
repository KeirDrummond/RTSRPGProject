// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectGameMode.h"
#include "ProjectPlayerController.h"
#include "ProjectAIController.h"
#include "GameFramework/HUD.h"
#include "PlayerCamera.h"
#include "UObject/ConstructorHelpers.h"

AProjectGameMode::AProjectGameMode()
{
	PlayerControllerClass = AProjectPlayerController::StaticClass();
	DefaultPawnClass = APlayerCamera::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHUDBPClass(TEXT("/Game/UserInterface/TheHUD"));
	if (PlayerHUDBPClass.Class != NULL)
	{
		HUDClass = PlayerHUDBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APawn> AIPlayerClass(TEXT("/Game/AI/AIPawn"));
	AIPlayer = AIPlayerClass.Class;
}

void AProjectGameMode::BeginPlay() {
	Super::BeginPlay();

	APlayerController* thePlayer = GetWorld()->GetFirstPlayerController();
	
	APawn* AIPawn = GetWorld()->SpawnActor<APawn>(AIPlayer, FVector(0.f, 0.f, 0.f), FRotator::ZeroRotator);
	AProjectAIController* theAI = Cast<AProjectAIController>(AIPawn->GetController());

	playerList.Add(thePlayer);
	playerList.Add(theAI);
}

TArray<AController*> AProjectGameMode::GetPlayerList() { return playerList; }
AController* AProjectGameMode::GetPlayer(int value) { 
	if (value < playerList.Num()) { 
		return playerList[value];
	} else {
		return NULL;
	}
}