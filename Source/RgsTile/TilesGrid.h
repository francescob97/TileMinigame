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
	void GenerateGrid(const int32 TileGridSize);

	void SpawnGridTiles(const int32 TileGridSize);

	void DestroyGrid();

	void InitTilesType(const int32 TypeTilesToSpawn, const ETileType Type);

	UPROPERTY(EditDefaultsOnly, Category = Configuration)
	TSubclassOf<ATile> TileClass;

	UPROPERTY()
	TArray<ATile*> TileArray;

private:
	TArray<int32> RandomIndexes;
	int32 RandomIndexesCounter = 0;


};
