// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectGameMode.h"
#include "ProjectPlayerController.h"
#include "PlayerCamera.h"

AProjectGameMode::AProjectGameMode()
{
	PlayerControllerClass = AProjectPlayerController::StaticClass();
	DefaultPawnClass = APlayerCamera::StaticClass();
}