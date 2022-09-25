// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Main_Utilities.h"
#include "MainClass.generated.h"

class ALevelStreamerActor;
class ALevelSystemIlumination;
class APlayerCharacter;

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

	//
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> LevelSystemIluminationActor;

	//
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> LevelStreamerActor;

	//
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> PlayerCharacterActor;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	//! Set the new game state
	virtual void SetGameState(MainUtilities::GameStateEnum gameState) { GameState = static_cast<int>(gameState); };

	//! Set the new generation state
	virtual void SetGenerationState(MainUtilities::GenerationStepsEnum generationState) { GenerationState = static_cast<int>(generationState); };

	//! Function that start the game
	virtual void StartGame();

	//! Function that send to stop the game at any time (Unexpected / intended)
	virtual void EndGame(bool IsPLayerDead);

	// Spawn the level streamer actor and store the ref
	virtual void SpawnLevelStreamerActor();

	// Spawn the level system ilumination actor and store the ref 
	virtual void SpawnLevelSystemIluminationActor();

	// Spawn the player character actor and store the ref 
	virtual void SpawnPlayerCharacterActor();

	// Spawn the enemy actor and store the ref 
	virtual void SpawnEnemyActor();

	// Creates the db interface and start merging it.
	virtual void SetupDataBases();

	// Calls to render the map and objects inside it.
	virtual void GenerateWorld();

	// Helper function 
	virtual void Log(MainUtilities::LogEnum logId, MainUtilities::GenerationTypeEnum type);

	// WorldRef
	UWorld* OwningWorld;

	// Level Streamer Ref
	ALevelStreamerActor* LevelStreamerClass;

	// Level Light System Ref
	ALevelSystemIlumination* LevelSystemIlumination;

	// Player Character Ref
	APlayerCharacter* PlayerCharacter;

	int GameState;

	int GenerationState;
};
