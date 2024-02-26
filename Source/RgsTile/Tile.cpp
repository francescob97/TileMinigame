// Copyright(c) Forge Reply. All Rights Reserved.

#include "Tile.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstance.h"


ATile::ATile()
{
	if (!IsValid(RootComponent))
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	}

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Game/Geometry/Meshes/ChamferBox"));
	MeshComponent->SetStaticMesh(CubeMesh.Object);
	MeshComponent->SetRelativeScale3D(FVector(2.0f, 2.0f, 1.0f));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> TimeMaterialInstance(TEXT("/Game/Materials/TileMaterialInstance"));
	MeshComponent->SetMaterial(0, TimeMaterialInstance.Object);
	MeshComponent->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = true;
}

void ATile::BeginPlay()
{
	Super::BeginPlay();
	
	MeshComponent->SetVectorParameterValueOnMaterials(FName("TileBaseColor"), FVector(FColor::Silver));
	MeshComponent->SetScalarParameterValueOnMaterials(FName("TileEmission"), 0.0f);
}


void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATile::SetType(ETileType Type)
{
	TileType = Type;
}

ETileType ATile::GetType() const
{
	return TileType;
}

void ATile::StepOn()
{
	FColor ColorToSet = FColor::Silver;
	switch (TileType)
	{
	case ETileType::Normal:
		ColorToSet = FColor::Silver; break;
	case ETileType::Green:
		ColorToSet = FColor::Green; break;
	case ETileType::Red:
		ColorToSet = FColor::Red; break;
	}

	MeshComponent->SetVectorParameterValueOnMaterials(FName("TileBaseColor"), FVector(ColorToSet));
	MeshComponent->SetScalarParameterValueOnMaterials(FName("TileEmission"), 1.0f);
}

void ATile::StepOff()
{
	if (TileType == ETileType::Normal)
	{
		MeshComponent->SetVectorParameterValueOnMaterials(FName("TileBaseColor"), FVector(FColor::Silver));
		MeshComponent->SetScalarParameterValueOnMaterials(FName("TileEmission"), 0.0f);
	}
}

void ATile::SetRowAndColumn(int32 Row, int32 Column)
{
	RowIndex = Row;
	ColumnIndex = Column;
}

int32 ATile::GetRowIndex() const
{
	return RowIndex;
}

int32 ATile::GetColumnIndex() const
{
	return ColumnIndex;
}

