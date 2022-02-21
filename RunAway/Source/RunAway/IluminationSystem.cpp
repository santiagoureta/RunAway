// Fill out your copyright notice in the Description page of Project Settings.


#include "IluminationSystem.h"
#include "Components/SpotLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

AIluminationSystem::AIluminationSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AIluminationSystem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIluminationSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

