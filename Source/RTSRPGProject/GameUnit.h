// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameUnit.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class RTSRPGPROJECT_API UGameUnit : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTSRPGPROJECT_API IGameUnit
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void UpdateColour();

	virtual bool GetIsSelected();
	virtual void SetSelected(bool value);

};
