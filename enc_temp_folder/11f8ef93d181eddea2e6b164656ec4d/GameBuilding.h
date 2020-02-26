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

	UFUNCTION(BlueprintCallable, meta=(DeterminesOutputType="ObjClass"))
		AGameCharacter* CreateUnit(TSubclassOf<AGameCharacter> unit);

	UFUNCTION(BlueprintCallable)
		bool AddToQueue(TSoftClassPtr<AGameCharacter> unit);

	float progress;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USceneComponent* spawnPoint;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void UpdateColour();

	void OnClick();

	bool GetIsSelected();

	virtual void SetSelected_Implementation(bool value) override;

private:

	bool selected;

};
