// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "RTSRPGProjectGameMode.h"
#include "RTSRPGProjectPlayerController.h"
#include "RTSRPGProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARTSRPGProjectGameMode::ARTSRPGProjectGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ARTSRPGProjectPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}