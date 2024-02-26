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


void ATilesGrid::GenerateGrid(const int32 TileGridSize)
{
	SpawnGridTiles(TileGridSize);

	RandomIndexesCounter = TileGridSize * TileGridSize - 1;
	
	for (int32 i = 0; i < RandomIndexesCounter; i++)
	{
		RandomIndexes.Add(i);
	}
}

void ATilesGrid::SpawnGridTiles(const int32 TileGridSize)
{
	const int IndexStart = TileGridSize / 2;
	const int IndexEnd = TileGridSize % 2 == 0 ? IndexStart - 1 : IndexStart;
	
	for (int32 Row = -IndexStart; Row <= IndexEnd; Row++)
	{
		for (int32 Column = -IndexStart; Column <= IndexEnd; Column++)
		{
			if(Row == 0 && Column == 0) continue;
			
			ATile* NewTile = GetWorld()->SpawnActor<ATile>(TileClass, FVector::ZeroVector, FRotator::ZeroRotator);

			if(NewTile)
			{
				FVector TilePosition = FVector(- Row * NewTile->TileSize * 100.f, Column * NewTile->TileSize * 100.f,  - 50.f);			
				NewTile->SetActorLocation(TilePosition);	
				NewTile->SetRowAndColumn(Row + IndexStart, Column + IndexStart);
				NewTile->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
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