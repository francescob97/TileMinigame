// Fill out your copyright notice in the Description page of Project Settings.


#include "TilesGrid.h"
#include "Tile.h"
#include "TileBlue.h"
#include "TileCommon.h"
#include "TileGreen.h"
#include "TileRed.h"

FOnTurnTileDelegate ATilesGrid::OnTurnOnAllGreenDelegate;
FOnTurnTileDelegate ATilesGrid::OnTurnOffAllGreenDelegate;

ATilesGrid::ATilesGrid()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ATilesGrid::BeginPlay()
{
	Super::BeginPlay();	
}

void ATilesGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ATilesGrid::SetGridSize(const int32 GridSize)
{
	TileGridSize = GridSize;

	CenterTileIndex = (GridSize / 2) * GridSize + GridSize / 2;
}

void ATilesGrid::CreateRedTiles(const int32 RedTilesToSpawn)
{
	for(int32 TileCounter = 0; TileCounter < RedTilesToSpawn; TileCounter++)
	{
		ATileRed* NewTile = GetWorld()->SpawnActor<ATileRed>(ATileRed::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		NewTile->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		TileArray.Add(NewTile);
	}	
}

void ATilesGrid::CreateGreenTiles(const int32 GreenTilesToSpawn)
{
	for(int32 TileCounter = 0; TileCounter < GreenTilesToSpawn; TileCounter++)
	{
		ATileGreen* NewTile = GetWorld()->SpawnActor<ATileGreen>(ATileGreen::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		NewTile->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		TileArray.Add(NewTile);		
	}	
}

void ATilesGrid::CreateBlueTiles(const int32 BlueTilesToSpawn)
{
	for(int32 TileCounter = 0; TileCounter < BlueTilesToSpawn; TileCounter++)
	{
		ATileBlue* NewTile = GetWorld()->SpawnActor<ATileBlue>(ATileBlue::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		NewTile->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		TileArray.Add(NewTile);	
	}	
}

void ATilesGrid::CreateCommonTiles()
{
	const int32 MissingTiles = TileGridSize * TileGridSize - TileArray.Num();
	for(int32 TileCounter = 0; TileCounter < MissingTiles; TileCounter++)
	{
		ATileCommon* NewTile = GetWorld()->SpawnActor<ATileCommon>(ATileCommon::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		NewTile->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		TileArray.Add(NewTile);
	}	
}

void ATilesGrid::ShuffleTilesInGrid()
{
	const int32 LastIndex = TileArray.Num() - 1;
	TileArray.Swap(LastIndex, CenterTileIndex);
	
	if (TileArray.Num() > 0)
	{	
		for (int32 i = 0; i <= LastIndex; i++)
		{			
			const int32 Index = FMath::RandRange(i, LastIndex);
			if (i != Index && Index != CenterTileIndex && i != CenterTileIndex)
			{
				TileArray.Swap(i, Index);
			}			
		}
	}
}

void ATilesGrid::SpawnGridTiles()
{	
	const int IndexStart = TileGridSize / 2;
	const int IndexEnd = TileGridSize % 2 == 0 ? IndexStart - 1 : IndexStart;
	
	for (int32 Row = -IndexStart; Row <= IndexEnd; Row++)
	{
		for (int32 Column = -IndexStart; Column <= IndexEnd; Column++)
		{			
			ATile* Tile = TileArray[TileGridSize * (Row + IndexStart) + Column + IndexStart];
			
			FVector TilePosition = FVector(- Row * Tile->TileSize * 100.f, Column * Tile->TileSize * 100.f,  - 50.f);	
			Tile->SetActorLocation(TilePosition);
			Tile->SetRowAndColumn(Row + IndexStart, Column + IndexStart);

			//Hide Starting Tile
			if(Row == 0 && Column == 0)				
				Tile->Hide();	
		}
	}
}

bool ATilesGrid::CheckTileType(const int32 Row, const int32 Col, const ETileType Type) const
{
	return TileArray[TileGridSize * Row + Col]->GetType() == Type;	
}

bool ATilesGrid::CheckTileNeverSteppedOn(const int32 Row, const int32 Col) const
{
	return TileArray[TileGridSize * Row + Col]->IsFirstTimeStepping();
}

int32 ATilesGrid::ComputeDistanceToTile(const int32 X, const int32 Y, const ETileType TileType) const
{
	bool bClosestTileFound = false;
	int32 Dist = 0;

	while (!bClosestTileFound && Dist <  2 * TileGridSize)
	{
		int jx, jy;
		
		for (int i = - Dist; i <= 0 && !bClosestTileFound; i++)
		{
			jx = - (i + Dist);
			jy =  i + Dist;
			
			if(!CheckOutOfBounds(X - i))
				continue;

			bClosestTileFound = (CheckOutOfBounds(Y - jx)
				&& CheckTileType(X - i, Y - jx, TileType))
				&& CheckTileNeverSteppedOn(X - i, Y - jx)
			||	(CheckOutOfBounds(Y - jy)
				&& CheckTileType(X - i, Y - jy, TileType))
				&& CheckTileNeverSteppedOn(X - i, Y - jy);	
		}

		for (int i = Dist; i > 0 && !bClosestTileFound; i--)
		{
			jx = - (i - Dist);
			jy =  i - Dist;
			
			if(!CheckOutOfBounds(X - i))
				continue;

			bClosestTileFound = (CheckOutOfBounds(Y - jx)
				&& CheckTileType(X - i, Y - jx, TileType))
				&& CheckTileNeverSteppedOn(X - i, Y - jx)
			|| (CheckOutOfBounds(Y - jy)
				&& CheckTileType(X - i, Y - jy, TileType))
				&& CheckTileNeverSteppedOn(X - i, Y - jy);		
		}	
		Dist++;
	}

	return Dist - 1;
}

bool ATilesGrid::CheckOutOfBounds(int Index) const
{
	return Index >= 0 && Index < TileGridSize;
}