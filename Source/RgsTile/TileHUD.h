// Copyright(c) Forge Reply. All Rights Reserved.

#pragma once

#include "GameFramework/HUD.h"

#include "TileHUD.generated.h"

UCLASS()
class RGSTILE_API ATileHUD : public AHUD
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
	void ShowEndScreen();
};
