// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightObject.generated.h"

UCLASS()
class RUNAWAY_API ALightObject : public AActor
{
	GENERATED_BODY()
	
public:	

	//! Contructors
	ALightObject();

	//! Getter to retrieve the level chunk where the light need to be attached
	int GetLevelChunkType() { return levelChunkType; };

	//! Setter that sets the level chunk name where the light need to be attached
	void SetLevelChunkType(int value) { levelChunkType = value; };

	//! Getter that retrieves the number of lights per level chunk
	int GetLevelLightsCount() { return lightsCountOnLevelChunk; };

	//! Setter that sets the num of lights to load on the level chunk
	void SetLevelLightsCount(int value) { lightsCountOnLevelChunk = value; };

	//! static mesh component ref
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LightInfo, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticLightMeshComp;

	//!///
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LightInfo, meta = (AllowPrivateAccess = "true"))
	class USpotLightComponent* LightComponent;

protected:

	//! Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	//! object properties
	int levelChunkType;
	int lightsCountOnLevelChunk;

};
