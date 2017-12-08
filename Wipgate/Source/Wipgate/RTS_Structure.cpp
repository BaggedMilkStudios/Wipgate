// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_Structure.h"

#include "Materials/MaterialInstanceDynamic.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

ARTS_Structure::ARTS_Structure()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//StaticMeshComponent->SetStaticMesh();

	UCapsuleComponent* CapsuleComponent = GetCapsuleComponent();
	CapsuleComponent->SetSimulatePhysics(true);

}

void ARTS_Structure::SetTeamMaterial()
{
	ARTS_Entity::SetTeamMaterial();

	if (StaticMeshComponent && StaticMeshComponent->GetMaterials().Num() > 0)
	{
		UMaterialInstanceDynamic* matInst = StaticMeshComponent->CreateAndSetMaterialInstanceDynamicFromMaterial(0, StaticMeshComponent->GetMaterial(0));
		matInst->SetVectorParameterValue("BodyColor", Team.Color);
	}
}