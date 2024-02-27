// Copyright(c) Forge Reply. All Rights Reserved.

#include "RgsTileGameMode.h"
#include "RgsTileCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Tile.h"
#include "TileHUD.h"
#include "Kismet/GameplayStatics.h"
#include "TilesGrid.h"
#include "Components/BoxComponent.h"

#define RAY_TILECHECK_LENGTH 100.f

ARgsTileGameMode::ARgsTileGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	OutOfGridTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("OutOfGridTrigger"));
	OutOfGridTrigger->SetWorldLocation(FVector(0.f, 0.f, -300.f));
	OutOfGridTrigger->SetBoxExtent(FVector(TileGridSize * 200.f, TileGridSize * 200.f, 100.f));
}

void ARgsTileGameMode::ResetGame()
{
	UGameplayStatics::OpenLevel(this, FName("/Game/Levels/LoadingLevel"));
}

int32 ARgsTileGameMode::GetTotalGreenTiles()
{	
	return GreenTilesToSpawn;
}

int32 ARgsTileGameMode::GetGreenTilesFound()
{	
	return GreenTilesStepCounter;
}

int32 ARgsTileGameMode::GetTotalRedTiles()
{	
	return RedTilesToSpawn;
}

int32 ARgsTileGameMode::GetRedTilesFound()
{	
	return RedTilesStepCounter;
}

int32 ARgsTileGameMode::GetClosestGreenTileDistance()
{
	return ClosestGreenTileDistance;
}

int32 ARgsTileGameMode::GetClosestRedTileDistance()
{	
	return ClosestRedTileDistance;
}

void ARgsTileGameMode::CheckSteppedTile()
{
	ACharacter* CharRef = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if(!CharRef) return;

	FVector Start = CharRef->GetActorLocation();
	FVector End = Start - FVector(0.f, 0.f, RAY_TILECHECK_LENGTH);
	FHitResult HitResult;
	FCollisionQueryParams Params;

	bool bHit = CharRef->GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_GameTraceChannel1, Params);

	if (!bHit)
	{
		if(PrevSteppedTile)
		{
			PrevSteppedTile->StepOff();
			PrevSteppedTile = nullptr;
		}		
		return;
	}
			
	NewSteppedTile = Cast<ATile>(HitResult.GetActor());

	if(PrevSteppedTile != NewSteppedTile)
	{
		// Check if first time stepping
		if(NewSteppedTile && NewSteppedTile->IsFirstTimeStepping())
		{
			if(NewSteppedTile->GetType() == ETileType::Green)
				GreenTilesStepCounter ++;

			if(NewSteppedTile->GetType() == ETileType::Red)
				RedTilesStepCounter ++;

			NewSteppedTile->SetFirstTimeStepOn();
		}

		if(PrevSteppedTile && NewSteppedTile)
		{
			PrevSteppedTile->StepOff();
			NewSteppedTile -> StepOn();
		}
		else if(!PrevSteppedTile && NewSteppedTile)
		{
			//e.g. Jumping
			NewSteppedTile->StepOn();
		}

		PrevSteppedTile = NewSteppedTile;

		ClosestGreenTileDistance = TilesGrid->ComputeDistanceToTile(NewSteppedTile->GetRowIndex(), NewSteppedTile->GetColumnIndex(), ETileType::Green);
		ClosestRedTileDistance = TilesGrid->ComputeDistanceToTile(NewSteppedTile->GetRowIndex(), NewSteppedTile->GetColumnIndex(), ETileType::Red);
	}	
}

void ARgsTileGameMode::CheckWinCondition()
{	
	if(GreenTilesStepCounter == GreenTilesToSpawn)
	{		
		EndGame();
	}
}

void ARgsTileGameMode::CheckLoseCondition()
{	
	if(RedTilesStepCounter == RedTilesToSpawn)
	{		
		EndGame();
	}	
}

void ARgsTileGameMode::EndGame()
{
	if(HUD)
	{
		HUD->ShowEndScreen();
	}	
	
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->SetIgnoreMoveInput(true);
		PlayerController->SetIgnoreLookInput(true);
	}
	
	GetWorldTimerManager().SetTimer(EndGame_TimerHandle, this, &ARgsTileGameMode::ResetGame, GameResetWaitSeconds, false);	
}

void ARgsTileGameMode::BeginPlay()
{
	Super::BeginPlay();

	check(TileGridSize >= 3);
	check(GreenTilesToSpawn >= 1);
	check(RedTilesToSpawn >= 1);
	check(TileGridSize * TileGridSize >= GreenTilesToSpawn + RedTilesToSpawn);

	OutOfGridTrigger->OnComponentBeginOverlap.AddDynamic(this, &ARgsTileGameMode::OnPlayerOverlap);

	HUD = Cast<ATileHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	TilesGrid = GetWorld()->SpawnActor<ATilesGrid>(TileGridClass, FVector::ZeroVector, FRotator::ZeroRotator);
	
	if (TilesGrid)
	{
		TilesGrid->SetGridSize(TileGridSize);
		TilesGrid->CreateGreenTiles(GreenTilesToSpawn);
		TilesGrid->CreateRedTiles(RedTilesToSpawn);
		TilesGrid->CreateBlueTiles(BlueTilesToSpawn);
		TilesGrid->CreateCommonTiles();
		TilesGrid->ShuffleTilesInGrid();
		TilesGrid->SpawnGridTiles();
	}
}

void ARgsTileGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckSteppedTile();
	CheckWinCondition();
	CheckLoseCondition();
}

void ARgsTileGameMode::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor);
	if (PlayerCharacter)
	{
		ResetGame();
	}
}