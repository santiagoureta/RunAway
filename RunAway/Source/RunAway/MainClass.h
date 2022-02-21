// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Main_Utilities.h"
#include "MainClass.generated.h"

class ALevelStreamerActor;

UCLASS()
class RUNAWAY_API AMainClass : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AMainClass();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//! Get the current game state
	virtual int GetGameState() const { return GameState; };

	//! Get the current generation state
	virtual int GetGenrationState() const { return GenerationState; };

	int GameState;

	int GenerationState;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	//! Set the new game state
	virtual void SetGameState(MainUtilities::GameStateEnum gameState) { GameState = static_cast<int>(gameState); };

	//! Set the new generation state
	virtual void SetGenerationState(MainUtilities::GenerationStepsEnum generationState) { GenerationState = static_cast<int>(generationState); };

	//!
	virtual void StartGame();

	//!
	virtual void EndGame();

	// Creates the db interface and start merging it.
	virtual void SetupDataBases();

	// Calls to render the map and objects inside it.
	virtual void GenerateWorld();

	// WorldRef
	UWorld* OwningWorld;

	// Level Streamer Ref
	ALevelStreamerActor* LevelStreamerClass;
};
