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

	if(TilesGrid)
	{
		TilesGrid->ShowAllGreenTiles();
	}	
}

void ATileBlue::StepOff()
{
	Super::StepOff();

	TurnOffTile();

	if(TilesGrid)
	{
		TilesGrid->HideAllGreenUnsteppedTiles();
	}	
}
