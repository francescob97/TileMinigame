// Fill out your copyright notice in the Description page of Project Settings.


#include "TileGreen.h"

#include "TilesGrid.h"

ATileGreen::ATileGreen()
{
	ColorToSet = FColor::Green;
	TileType = ETileType::Green;
}

void ATileGreen::BeginPlay()
{
	Super::BeginPlay();

	ATilesGrid::OnTurnOnAllGreenDelegate.AddDynamic(this, &ATileGreen::StepOn);
	ATilesGrid::OnTurnOffAllGreenDelegate.AddDynamic(this, &ATileGreen::StepOff);	
}

void ATileGreen::StepOff()
{
	Super::StepOff();

	if(IsFirstTimeStepping())
		TurnOffTile();;
}
