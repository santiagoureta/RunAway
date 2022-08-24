// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelSystemIlumination.generated.h"

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

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:

	//! flag to return
	bool isSystemReady;

	virtual void GetLightList();
};
