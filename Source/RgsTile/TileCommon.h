// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include "TileCommon.generated.h"

/**
 * 
 */
UCLASS()
class RGSTILE_API ATileCommon : public ATile
{
	GENERATED_BODY()

public:
	
	virtual void StepOff() override;
	
};
