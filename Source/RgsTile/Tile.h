// Copyright(c) Forge Reply. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UENUM()
enum class ETileType : uint8
{
	Normal,
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
	void StepOff();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Visual, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

protected:

	UPROPERTY(Transient)
	ETileType TileType = ETileType::Normal;
};
