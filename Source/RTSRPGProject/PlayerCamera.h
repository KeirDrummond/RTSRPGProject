// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCamera.generated.h"

UCLASS(Blueprintable)
class RTSRPGPROJECT_API APlayerCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCamera();

public:
	// Called on start
	virtual void BeginPlay() override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	// Camera control properties/restrictions
	UPROPERTY(EditDefaultsOnly, Category = Camera)
		float minimumZoom;
	UPROPERTY(EditDefaultsOnly, Category = Camera)
		float maximumZoom;
	UPROPERTY(EditDefaultsOnly, Category = Camera)
		float cameraSpeed;
	UPROPERTY(EditDefaultsOnly, Category = Camera)
		float xBound;
	UPROPERTY(EditDefaultsOnly, Category = Camera)
		float yBound;

	// Camera controls	

	void MoveCamera(float posX, float posY);
	void ZoomCamera(float axisValue);

private:

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;



};