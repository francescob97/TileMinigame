// Fill out your copyright notice in the Description page of Project Settings.


#include "TilesGrid.h"
#include "Kismet/KismetMathLibrary.h"
#include "Tile.h"

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


void ATilesGrid::GenerateGrid(const int32 tileGridSize)
{
	TileGridSize = tileGridSize;
	SpawnGridTiles();

	RandomIndexesCounter = TileGridSize * TileGridSize - 1;
	
	for (int32 i = 0; i <= RandomIndexesCounter; i++)
	{
		if(i != CenterTileIndex)
			RandomIndexes.Add(i);
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
			ATile* NewTile = GetWorld()->SpawnActor<ATile>(TileClass, FVector::ZeroVector, FRotator::ZeroRotator);

			if(NewTile)
			{
				FVector TilePosition = FVector(- Row * NewTile->TileSize * 100.f, Column * NewTile->TileSize * 100.f,  - 50.f);			
				NewTile->SetActorLocation(TilePosition);	
				NewTile->SetRowAndColumn(Row + IndexStart, Column + IndexStart);
				NewTile->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			}				

			if(Row == 0 && Column == 0)
			{
				CenterTileIndex = IndexStart * TileGridSize + IndexStart;
				NewTile->Hide();
			}				
			
			TileArray.Add(NewTile);			
		}
	}
}

void ATilesGrid::DestroyGrid()
{
	for (const ATile* Tile : TileArray)
	{
		
		//Destroy();
	}

	TileArray.Reset();
	TileGridSize = 0;
}

void ATilesGrid::InitTilesType(const int32 TypeTilesToSpawn, const ETileType Type)
{	
	for(int32 TypeCounter = 0; TypeCounter < TypeTilesToSpawn; TypeCounter++)
	{
		const int32 Index = UKismetMathLibrary::RandomIntegerInRange(0, RandomIndexesCounter - 1);
		TileArray[RandomIndexes[Index]]->SetType(Type);
		
		RandomIndexes.Swap(Index, RandomIndexesCounter - 1);		
		RandomIndexesCounter--;
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
