// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectGameMode.h"
#include "ProjectPlayerController.h"
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
}