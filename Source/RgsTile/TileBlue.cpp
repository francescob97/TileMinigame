// Fill out your copyright notice in the Description page of Project Settings.


#include "TileBlue.h"
#include "TilesGrid.h"

ATileBlue::ATileBlue()
{
	ColorToSet = FColor::Blue;
	TileType = ETileType::Blue;
}

void ATileBlue::StepOn()
{
	Super::StepOn();

	ATilesGrid::OnTurnOnAllGreenDelegate.Broadcast();
}

void ATileBlue::StepOff()
{
	Super::StepOff();

	TurnOffTile();

	ATilesGrid::OnTurnOffAllGreenDelegate.Broadcast();
}
