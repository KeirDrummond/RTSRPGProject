// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ProjectGameMode.h"
#include "GameFramework/Controller.h"
#include "GameCharacter.h"
#include "ProjectAIController.generated.h"

UENUM(BlueprintType)
enum class SquadState : uint8
{
	Reserve UMETA(DisplayName = "Reserve"),
	Defend UMETA(DisplayName = "Defend"),
	Attack UMETA(DisplayName = "Attack"),
	Retreat UMETA(DisplayName = "Retreat")
};

USTRUCT(BlueprintType)
struct FSquad
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AGameCharacter*> units;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector destination;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		SquadState wantedState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		SquadState currentState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float power;

	FSquad() : destination(FVector(0.f, 0.f, 0.f)), wantedState(SquadState::Reserve), currentState(SquadState::Reserve), power(0.f)
	{

	}
};
/**
 * 
 */
UCLASS()
class RTSRPGPROJECT_API AProjectAIController : public AAIController
{
	GENERATED_BODY()

public:

	AProjectAIController();

	void NewUnit(AGameCharacter* unit);
	void LostUnit(AGameCharacter* unit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FSquad> squads;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AGameCharacter*> selection;

	UFUNCTION(BlueprintCallable)
		void CommandMoveToLocation(AGameCharacter *unit, FVector location);

	UFUNCTION(BlueprintCallable)
		void CommandAttackMoveToLocation(AGameCharacter *unit, FVector location);

	void AddToReserveSquad(AGameCharacter* unit);

	UFUNCTION(BlueprintCallable)
		void AddToSquad(AGameCharacter* unit, int32 index);

	UFUNCTION(BlueprintCallable)
		void RemoveFromSquad(AGameCharacter* unit, int32 index);

};
