// Copyright(c) Forge Reply. All Rights Reserved.

#include "RgsTileGameMode.h"
#include "RgsTileCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Tile.h"
#include "Kismet/GameplayStatics.h"
#include "TileHUD.h"
#include "TilesGrid.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/KismetMathLibrary.h"


ARgsTileGameMode::ARgsTileGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ARgsTileGameMode::ResetGame()
{
	UGameplayStatics::OpenLevel(this, FName("/Game/Levels/LoadingLevel"));
}

int32 ARgsTileGameMode::GetTotalGreenTiles()
{
	//TODO: implementation
	return -1;
}

int32 ARgsTileGameMode::GetGreenTilesFound()
{
	//TODO: implementation
	return -1;
}

int32 ARgsTileGameMode::GetTotalRedTiles()
{
	//TODO: implementation
	return -1;
}

int32 ARgsTileGameMode::GetRedTilesFound()
{
	//TODO: implementation
	return -1;
}

int32 ARgsTileGameMode::GetClosestGreenTileDistance()
{
	//TODO: implementation
	return -1;
}

int32 ARgsTileGameMode::GetClosestRedTileDistance()
{
	//TODO: implementation
	return -1;
}

void ARgsTileGameMode::BeginPlay()
{
	Super::BeginPlay();

	//TODO: implementation
	TilesGrid = GetWorld()->SpawnActor<ATilesGrid>(TileGridClass, FVector::ZeroVector, FRotator::ZeroRotator);

	if (TilesGrid)
	{
		TilesGrid->GenerateGrid(TileGridSize);
		TilesGrid->InitTilesType(GreenTilesToSpawn, ETileType::Green);
		TilesGrid->InitTilesType(RedTilesToSpawn, ETileType::Red);
	}
}

void ARgsTileGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//TODO: implementation
}

