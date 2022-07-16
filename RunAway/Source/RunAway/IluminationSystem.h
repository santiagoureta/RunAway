// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IluminationSystem.generated.h"

UCLASS()
class RUNAWAY_API AIluminationSystem : public AActor
{
	GENERATED_BODY()
	
public:	

	//! Contructors
	AIluminationSystem();

	//! Getter to retrieve the level chunk where the light need to be attached
	int GetLevelChunkType() { return levelChunkType; };

	//! Setter that sets the level chunk name where the light need to be attached
	void SetLevelChunkType(int value) { levelChunkType = value; };

	//! Getter to retrieve the level chunk where the light need to be attached
	FVector& GetLevelChunkDirection() { return Direction; };

	//! Setter that sets the level chunk name where the light need to be attached
	void SetLevelChunkDirection(FVector& value) { Direction = value; };

	//! Getter to retrieve the level chunk where the light need to be attached
	FVector& GetLevelChunkPosition() { return levelChunkPosition; };

	//! Setter that sets the level chunk name where the light need to be attached
	void SetLevelChunkPosition(FVector& value) { levelChunkPosition = value; };

	//! Getter that retrieves the number of lights per level chunk
	int GetLevelLightsCount() { return lightsCountOnLevelChunk; };

	//! Setter that sets the num of lights to load on the level chunk
	void SetLevelLightsCount(int value) { lightsCountOnLevelChunk = value; };

	//! Function that overrides the position for the current light object to display correctly on the world for each level chunk
	void OverrideLightPosition(FVector lightPosition, FVector Direction);

protected:

	//! Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	//! static mesh component ref
	UStaticMeshComponent* StaticMeshComp;

	//! object properties
	int levelChunkType;
	FVector levelChunkPosition;
	FVector Direction;
	int lightsCountOnLevelChunk;

};
