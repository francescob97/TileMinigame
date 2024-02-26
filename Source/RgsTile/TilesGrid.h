// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TilesGrid.generated.h"

class ATile;
enum class ETileType : uint8;

UCLASS()
class RGSTILE_API ATilesGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	ATilesGrid();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	// Grid of Tiles generation
	void GenerateGrid(const int32 TileGridSize);

	// Spawn of all the Tiles that make up the grid
	void SpawnGridTiles();

	// Grid Destruction with all its Tiles
	void DestroyGrid();

	// Type Initialization for all Tiles inside Grid
	void InitTilesType(const int32 TypeTilesToSpawn, const ETileType Type);

	// Returns if a Tile is of a certain Type
	bool CheckTileType(const int32 Row, const int32 Col, const ETileType Type) const;

	// Check for closest TileType Tile and return distance
	int32 ComputeDistanceToTile(const int32 X, const int32 Y, const ETileType TileType) const;

	// Check for Grid Matrix 
	bool CheckOutOfBounds(int Index) const;

	UPROPERTY(EditDefaultsOnly, Category = Configuration)
	TSubclassOf<ATile> TileClass;

	// Matrix Grid as Row-major
	UPROPERTY()
	TArray<ATile*> TileArray;

private:

	// Size of the Grid matrix
	int32 TileGridSize;

	// Array of indexes used to guarantee distinct random values
	TArray<int32> RandomIndexes;

	// Counter indicating random elements available
	int32 RandomIndexesCounter = 0;

	// Index of the starting point
	int32 CenterTileIndex;
};
