// Copyright(c) Forge Reply. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UENUM()
enum class ETileType : uint8
{
	Common,
	Green,
	Red
};

// Simple implementation of the Tile class.
// It consist in a platform sized 2m x 2m x 1m.
UCLASS()
class RGSTILE_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	ATile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	// Sets the type of this tile.
	void SetType(ETileType Type);

	// Returns the type of this tile.
	ETileType GetType() const;

	// Method to call to notify when the player steps on this tile.
	void StepOn();

	// Method to call to notify when the player steps off this tile.
	virtual void StepOff();

	// Setting Row and Column indexes of the Tile inside grid
	void SetRowAndColumn(const int32 Row, const int32 Column);

	// Setting that the platform has been stepped on at least once
	void SetFirstTimeStepOn();

	// Hide the Tile from view
	void Hide() const;

	// Tile row inside grid
	int32 GetRowIndex() const;

	// Tile Column inside grid
	int32 GetColumnIndex() const;

	// Check if Tile has already been stepped on
	bool IsFirstTimeStepping() const;

	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Visual, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere)
	float TileSize = 2.f;

	UPROPERTY(VisibleAnywhere)
	FColor ColorToSet = FColor::Silver;

protected:

	UPROPERTY(Transient)
	ETileType TileType = ETileType::Common;
	
	//Row Index of the Tile inside grid
	int32 RowIndex;

	//Column Index of the Tile inside grid
	int32 ColumnIndex;

	//States if Tile has been already stepped on
	bool bSteppedOn = false;
};
