// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameUnit.h"
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

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Unit)
		int32 defaultOwner;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Unit)
		AController* owningPlayer;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Unit)
		FString name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Unit)
		float basePower;
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

	UFUNCTION(BlueprintCallable)
		void AttackTarget(UObject* target);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void UpdateColour();

	void MoveToPosition(FVector target);

	UFUNCTION(BlueprintPure)
		bool GetIsSelected();

	AController* GetOwningPlayer();
	void SetSelected(bool value);

	float power;

private:

	bool selected;

	class AProjectPlayerController* playerController;
	class AAIController* theAIController;

	float CalculatePower();

};