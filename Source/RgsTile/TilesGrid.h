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
	void SetGridSize(const int32 GridSize);

	// Fill TilesArray with Red Tiles
	void CreateRedTiles(const int32 RedTilesToSpawn);

	// Fill TilesArray with Green Tiles
	void CreateGreenTiles(const int32 GreenTilesToSpawn);

	// Fill TilesArray with Blue Tiles
	void CreateBlueTiles(const int32 BlueTilesToSpawn);

	// Fill remaining TilesArray cells with Common Tiles
	void CreateCommonTiles();

	//Shuffle the tiles to arrange the tiles randomly
	void ShuffleTilesInGrid();

	// Spawn of all the Tiles that make up the grid
	void SpawnGridTiles();
	
	// Returns if a Tile is of a certain Type
	bool CheckTileType(const int32 Row, const int32 Col, const ETileType Type) const;

	// Returns if a Tile is already Stepped on
	bool CheckTileNeverSteppedOn(const int32 Row, const int32 Col) const;
	
	// Check for closest TileType Tile and return distance
	int32 ComputeDistanceToTile(const int32 X, const int32 Y, const ETileType TileType) const;

	// Check for Grid Matrix 
	bool CheckOutOfBounds(int Index) const;

	// Turn on all Green Tiles
	void ShowAllGreenTiles();

	// Turn off new Green Tiles
	void HideAllGreenUnsteppedTiles();
	
	// Matrix Grid as Row-major
	UPROPERTY()
	TArray<ATile*> TileArray;

private:

	// Size of the Grid matrix
	int32 TileGridSize;

	// Index of the starting point
	int32 CenterTileIndex;
};
