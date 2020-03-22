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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Determines who owns this unit on game start
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Unit)
		int32 defaultOwner;
	// The pawn of the owned unit
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Unit)
		APawn* owningPlayer;

	// Identifier
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Unit)
		FString name;

	// A base power value used to evaluate how good a unit might be
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Unit)
		float basePower;

	// Combat properties
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Unit)
		int32 health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
		int32 maxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
		int32 attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
		int32 defence;
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

	APawn* GetOwningPlayer() override;

private:

	bool selected;

	AAIController* theAIController;

};