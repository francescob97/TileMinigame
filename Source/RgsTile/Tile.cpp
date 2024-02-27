// Copyright(c) Forge Reply. All Rights Reserved.

#include "Tile.h"

#include "Components/BoxComponent.h"
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

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollider"));
	BoxCollider->SetBoxExtent(FVector(100.f, 100.f, 50.f));
	BoxCollider->SetupAttachment(RootComponent);

	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxCollider->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	BoxCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);	

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
	MeshComponent->SetVectorParameterValueOnMaterials(FName("TileBaseColor"), FVector(ColorToSet));
	MeshComponent->SetScalarParameterValueOnMaterials(FName("TileEmission"), 1.0f);	
}

void ATile::StepOff()
{

}

void ATile::SetRowAndColumn(const int32 Row, const int32 Column)
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

bool ATile::IsFirstTimeStepping() const
{
	return !bSteppedOn;
}

void ATile::SetFirstTimeStepOn()
{
	bSteppedOn = true;
}

void ATile::Hide() const
{
	MeshComponent->SetVisibility(false);
}

