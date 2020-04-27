// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "GameUnit.h"
#include "DetourCrowdAIController.h"
#include "CharacterAIController.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ECommandsEnum : uint8
{
	CE_Idle UMETA(DisplayName = "Idle"),
	CE_Movement UMETA(DisplayName = "Movement"),
	CE_Attack UMETA(DisplayName = "Attack"),
	CE_AttackMove UMETA(DisplayName = "AttackMove"),
	CE_Dead UMETA(DisplayName = "Dead")
};

UCLASS()
class RTSRPGPROJECT_API ACharacterAIController : public AAIController
{
	GENERATED_BODY()

public:

	ACharacterAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:

	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	bool MoveToPosition(const FVector target);

	void DoCommand();

public:

	bool Idle();
	bool DoIdle();

	bool MoveCommand(const FVector destination);
	bool AttackCommand(AActor *target);

	bool AttackMoveCommand(const FVector destination);
	bool DoAttackMove(const FVector destination);

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		ECommandsEnum currentCommand;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FVector currentDestination;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		AActor *currentTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UAIPerceptionComponent* aiPerceptionComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UAISenseConfig_Sight* sightConfig;

	TArray<AActor*> GetPerception();
	
};