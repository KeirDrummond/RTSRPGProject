// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUnit.h"

// Add default functionality here for any IGameUnit functions that are not pure virtual.

APlayerState* IGameUnit::GetOwningPlayer()
{
	return nullptr;
}

bool IGameUnit::GetIsSelected()
{
	return false;
}

void IGameUnit::SetSelected(bool value)
{

}

void IGameUnit::TakeDamage(int32 damage)
{

}

bool IGameUnit::IsInteractable()
{
	return false;
}