// Fill out your copyright notice in the Description page of Project Settings.


#include "IluminationSystem.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Main_Utilities.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AIluminationSystem::AIluminationSystem()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Game/Assets/PolygonTown/Meshes/Props/SM_Prop_Streetlamp_01.SM_Prop_Streetlamp_01"));

	if (Asset.Succeeded())
	{
		//Attaching the Components and setting physics
		StaticMeshComp->SetupAttachment(RootComponent);
		StaticMeshComp->SetStaticMesh(Asset.Object);
		StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		StaticMeshComp->SetWorldScale3D(FVector(1.5f));
	}
}

void AIluminationSystem::OverrideLightPosition(FVector lightPosition, FVector Direction)
{
	StaticMeshComp->SetRelativeRotation(Direction.ToOrientationQuat());
	StaticMeshComp->SetRelativeLocation(lightPosition);
}

// Called when the game starts or when spawned
void AIluminationSystem::BeginPlay()
{
	Super::BeginPlay();
}

