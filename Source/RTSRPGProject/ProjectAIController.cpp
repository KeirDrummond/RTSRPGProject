// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectAIController.h"
#include "ProjectGameMode.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

AProjectAIController::AProjectAIController(){
	bWantsPlayerState = true;
}

void AProjectAIController::BeginPlay() {

	Super::BeginPlay();
}
