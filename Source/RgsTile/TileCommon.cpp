// Fill out your copyright notice in the Description page of Project Settings.


#include "TileCommon.h"

void ATileCommon::StepOff()
{
	Super::StepOff();

	MeshComponent->SetVectorParameterValueOnMaterials(FName("TileBaseColor"), FVector(FColor::Silver));
	MeshComponent->SetScalarParameterValueOnMaterials(FName("TileEmission"), 0.0f);
}
