// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameUnit.h"
#include "AIController.h"
#include "GameCharacter.generated.h"

UENUM(BlueprintType)
enum class PlayerID : uint8
{
	Player1 UMETA(DisplayName = "Player 1"),
	Player2 UMETA(DisplayName = "Player 2")
};

UENUM(BlueprintType)
enum class EUnitStateEnum : uint8
{
	CE_Idle UMETA(DisplayName = "Idle"),
	CE_Movement UMETA(DisplayName = "Movement"),
	CE_Attack UMETA(DisplayName = "Attack"),
	CE_Dead UMETA(DisplayName = "Dead")
};

UCLASS(Blueprintable)
class RTSRPGPROJECT_API AGameCharacter : public ACharacter, public IGameUnit
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGameCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Determines who owns this unit on game start
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Unit)
		int32 defaultOwner;
	// The pawn of the owned unit
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Unit)
		APlayerState* owningPlayer;
	void SetOwningPlayer(APlayerState* player);

	// Identifier
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Unit)
		FString name;

	// A base power value used to evaluate how good a unit might be
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Unit)
		float basePower;

	// Combat properties
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Unit)
		int32 health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Unit)
		int32 maxHealth;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Unit)
		int32 attack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Unit)
		int32 defence;

	// How many attacks can be performed per second.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
		int32 attackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
		float attackRange;

	// When called in the blueprint, updates the unit colour
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void UpdateColour();

	// Selection details
	UFUNCTION(BlueprintPure)
		bool GetIsSelected();

	void SetSelected(bool value) override;

	APlayerState* GetOwningPlayer() override;

	void TakeDamage(int32 damage);

	bool IsAlive() override;

	UPROPERTY(BlueprintReadOnly)
		bool alive;

	bool AttackTarget(AActor* target);

	void SetState(EUnitStateEnum state);

protected:

	UFUNCTION(BlueprintImplementableEvent)
		void SetStateBP(EUnitStateEnum state);

	bool selected;

	AAIController* theAIController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		EUnitStateEnum currentState;

	float attackCooldown;

	FVector currentDestination;
	AActor* currentTarget;
		
	void OnDeath();

protected:

	UFUNCTION(BlueprintImplementableEvent)
		void OnDeathBP();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void UpdateHealth();

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SetHealthColour();

};