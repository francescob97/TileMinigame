// Copyright(c) Forge Reply. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RgsTileGameMode.generated.h"

enum class ETileType : uint8;

UCLASS(minimalapi)
class ARgsTileGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARgsTileGameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Resets the game, by forcing the reload of the game level.
	void ResetGame();

	// Returns the total number of Green Tiles in the tile grid.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Game)
	int32 GetTotalGreenTiles();

	// Returns the number of Green Tiles that the player found.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Game)
	int32 GetGreenTilesFound();

	// Returns the total number of Red Tiles in the tile grid.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Game)
	int32 GetTotalRedTiles();

	// Returns the number of Red Tiles that the player found.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Game)
	int32 GetRedTilesFound();

	// Returns the distance from the player to the closest Green Tile (that the player has not found yet).
	// Returns -1 if all Green Tiles have been found.
	// Distance is defined as the number of tiles that the player has to move (horizontally and vertically)
	// to reach the closest Green Tile.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Game)
	int32 GetClosestGreenTileDistance();

	// Returns the distance from the player to the closest Red Tile (that the player has not found yet).
	// Returns -1 if all Red Tiles have been found.
	// Distance is defined as the number of tiles that the player has to move (horizontally and vertically)
	// to reach the closest Red Tile.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Game)
	int32 GetClosestRedTileDistance();

public:

	// Defines the size of the tile grid to generate.
	// Must be at least 3.
	// Can be changed in the "TileGameModeBP" blueprint.
	UPROPERTY(EditDefaultsOnly, Category = Configuration)
	int32 TileGridSize = 10;

	// Defines the number of Green Tiles to randomly place in the tile grid.
	// Must be at least 1.
	// Can be changed in the "TileGameModeBP" blueprint.
	UPROPERTY(EditDefaultsOnly, Category = Configuration)
	int32 GreenTilesToSpawn = 5;

	// Defines the number of Red Tiles to randomly place in the tile grid.
	// Must be at least 1.
	// Can be changed in the "TileGameModeBP" blueprint.
	UPROPERTY(EditDefaultsOnly, Category = Configuration)
	int32 RedTilesToSpawn = 5;

	//Tiles Grid Manager Object Class
	//Handles Grid spawning and Tiles Type Initialization
	UPROPERTY(EditDefaultsOnly, Category = Configuration)
	TSubclassOf<class ATilesGrid> TileGridClass;

private:

	// Check for a new stepped Tile by Raycast
	void CheckSteppedTile();	

	// Check if all Green Tiles have been stepped on
	bool CheckWinCondition() const;

	// Check if all Red Tiles have been stepped on
	bool CheckLoseCondition() const;		
	
	//Tiles Grid Manager Object
	UPROPERTY()
	class ATilesGrid* TilesGrid;

	// Green Tiles that have been stepped on at least once
	int32 GreenTilesStepCounter = 0;

	// Red Tiles that have been stepped on at least once
	int32 RedTilesStepCounter = 0;

	//Distance to the Green Tile closest to the player
	int32 ClosestGreenTileDistance = -1;

	//Distance to the Red Tile closest to the player
	int32 ClosestRedTileDistance = -1;

	UPROPERTY()
	class ATile* PrevSteppedTile;

	UPROPERTY()
	class ATile* NewSteppedTile;
};



