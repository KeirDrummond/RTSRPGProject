// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "ProjectPlayerController.h"

AGameHUD::AGameHUD() {
}

void AGameHUD::DrawHUD()
{
	if (drawBox){ DrawBox(); }
}

void AGameHUD::DrawBox() {
	DrawRect(FLinearColor(0, 0, 1, .15f), boxOrigin.X, boxOrigin.Y, boxEnd.X - boxOrigin.X, boxEnd.Y - boxOrigin.Y);
	unitsFound.Empty();
	GetActorsInSelectionRectangle<AActor>(boxOrigin, boxEnd, unitsFound, false, false);
	AProjectPlayerController* pc = Cast<AProjectPlayerController>(GetOwningPlayerController());	
	if (pc) { pc->UnitsInBox(unitsFound); }
}