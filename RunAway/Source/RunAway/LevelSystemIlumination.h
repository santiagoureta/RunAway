// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IluminationSystem.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Main_Utilities.h"
#include "LevelSystemIlumination.generated.h"

class AIluminationSystem;

UCLASS()
class RUNAWAY_API ALevelSystemIlumination : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ALevelSystemIlumination();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IluminationSystemReady();

	bool CreateLightSystem(TArray<AIluminationSystem*> &LightList);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:

	// AIluminationSystem ref
	AIluminationSystem* Asystem;

	//! flag to return
	bool isSystemReady;
};
