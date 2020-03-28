// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameUnit.h"
#include "AIController.h"
#include "GamePlayerState.h"
#include "GameCharacter.generated.h"

UENUM(BlueprintType)
enum class PlayerID : uint8
{
	Player1 UMETA(DisplayName = "Player 1"),
	Player2 UMETA(DisplayName = "Player 2")
};

UENUM(BlueprintType)
enum class ECommandsEnum : uint8
{
	CE_Idle UMETA(DisplayName="Idle"),
	CE_Movement UMETA(DisplayName="Movement"),
	CE_Attack UMETA(DisplayName="Attack")
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
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Unit)
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

	// Uses the character's AI to navigate to a destination
	void MoveToPosition(FVector target);

	// Selection details
	UFUNCTION(BlueprintPure)
		bool GetIsSelected();

	void SetSelected(bool value) override;

	APlayerState* GetOwningPlayer() override;

	// Commands
	void Idle();
	void MoveCommand(const FVector destination);
	bool AttackCommand(AActor* target);

	void TakeDamage(int32 damage);

	bool IsInteractable() override;

private:

	bool selected;

	AAIController* theAIController;

	ECommandsEnum currentCommand;

	// Called on frame updates to check if a new command needs to be done.
	void DoCommand();

	void AttackTarget(AActor* target);

	float attackCooldown;

	FVector currentDestination;
	AActor* currentTarget;	

	bool interactable;

protected:

	UFUNCTION(BlueprintImplementableEvent)
		void UpdateAnimation(ECommandsEnum command);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void UpdateHealth();

};