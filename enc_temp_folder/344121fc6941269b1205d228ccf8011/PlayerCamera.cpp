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
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	minimumZoom = 500.0f;
	maximumZoom = 2000.0f;
	cameraSpeed = 2.0f;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = maximumZoom;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

void APlayerCamera::BeginPlay() {
	GetWorld()->GetFirstPlayerController()->Possess(this);
	Super::BeginPlay();	
}

// Called every frame
void APlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCamera::MoveCamera(float dirX, float dirY) {

	FVector movement(dirX * cameraSpeed, dirY * cameraSpeed, 0);
	AddMovementInput(movement, 1);
}

void APlayerCamera::ZoomCamera(float AxisValue) {
	float targetValue = CameraBoom->TargetArmLength + AxisValue;	
	targetValue = FMath::Clamp(targetValue, minimumZoom, maximumZoom);
	CameraBoom->TargetArmLength = targetValue;
}

void APlayerCamera::CameraVertical(float AxisValue) { cameraVValue = AxisValue; }
void APlayerCamera::CameraHorizontal(float AxisValue) {	cameraHValue = AxisValue; }

// Called to bind functionality to input
void APlayerCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Zoom", this, &APlayerCamera::ZoomCamera);
	InputComponent->BindAxis("CameraVertical", this, &APlayerCamera::CameraVertical);
	InputComponent->BindAxis("CameraHorizontal", this, &APlayerCamera::CameraHorizontal);
}

