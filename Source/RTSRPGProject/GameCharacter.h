// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameUnit.h"
#include "GameCharacter.generated.h"

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Unit)
		FString name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Unit)
		int health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
		int maxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
		int attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
		int defence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
		int attackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Training)
		float trainingTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Training)
		float cost;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void UpdateColour();

	void MoveToPosition(FVector target);

	UFUNCTION(BlueprintPure)
		bool GetIsSelected();

	void SetSelected(bool value);

private:

	bool selected;

	class AProjectPlayerController* playerController;
	class AAIController* theAIController;

};