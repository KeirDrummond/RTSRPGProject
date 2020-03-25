// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameUnit.h"
#include "GameCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "GameBuilding.generated.h"

UCLASS(Blueprintable)
class RTSRPGPROJECT_API AGameBuilding : public AActor, public IGameUnit
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameBuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Unit owner

	// Determines who owns this unit on game start
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Unit)
		int32 defaultOwner;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Unit)
		APlayerState* owningPlayer;
	void SetOwningPlayer(APlayerState* player);

	// Identification

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Unit)
		FString name;

	// Combat properties

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Unit)
		int health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
		int maxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
		int defence;

	// Character creation function

	UFUNCTION(BlueprintCallable, meta=(DeterminesOutputType="ObjClass"))
		AGameCharacter* CreateUnit(TSubclassOf<AGameCharacter> unit);

	// Components

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USceneComponent* spawnPoint;

	// Selection data

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void UpdateColour();

	UFUNCTION(BlueprintPure)
		bool GetIsSelected();

	void SetSelected(bool value) override;

	APlayerState* GetOwningPlayer() override;

	void TakeDamage(int32 damage);

private:

	bool selected;

};
