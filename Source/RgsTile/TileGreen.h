// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include "TileGreen.generated.h"

/**
 * 
 */
UCLASS()
class RGSTILE_API ATileGreen : public ATile
{
	GENERATED_BODY()

public:
	ATileGreen();

	virtual void BeginPlay() override;

	virtual void StepOff() override;
};
