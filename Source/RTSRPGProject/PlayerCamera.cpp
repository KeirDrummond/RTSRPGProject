// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCamera.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Engine/GameViewportClient.h"
#include "Engine/Engine.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
APlayerCamera::APlayerCamera()
{
	PrimaryActorTick.bCanEverTick = false;

	minimumZoom = 500.0f;
	maximumZoom = 2000.0f;
	cameraSpeed = 6.0f;
	xBound = 0.0f;
	yBound = 0.0f;

	// Create a camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = maximumZoom;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

void APlayerCamera::BeginPlay() {
	GetWorld()->GetFirstPlayerController()->Possess(this);
	Super::BeginPlay();
}

void APlayerCamera::MoveCamera(float dirX, float dirY) {

	FVector movement(dirX * cameraSpeed, dirY * cameraSpeed, 0);
	AddMovementInput(movement, 1);
}

void APlayerCamera::ZoomCamera(float axisValue) {
	float targetValue = CameraBoom->TargetArmLength + axisValue;	
	targetValue = FMath::Clamp(targetValue, minimumZoom, maximumZoom);
	CameraBoom->TargetArmLength = targetValue;
}