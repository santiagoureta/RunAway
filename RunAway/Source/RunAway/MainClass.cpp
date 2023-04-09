// Fill out your copyright notice in the Description page of Project Settings.


#include "MainClass.h"
#include "LevelStreamerActor.h"
#include "UObject/ConstructorHelpers.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "LevelSystemIlumination.h"
#include "PlayerCharacter.h"
#include "EnemyCharacter.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

//---------------------------------------------------------------------------
//	CONSTRUCTOR
//---------------------------------------------------------------------------
AMainClass::AMainClass()
{
	PrimaryActorTick.bCanEverTick = true;
}

//---------------------------------------------------------------------------
//	BEGIN PLAY
//---------------------------------------------------------------------------
void AMainClass::BeginPlay()
{
    OwningWorld = GetWorld();

    Super::BeginPlay();
}

//---------------------------------------------------------------------------
//	TICK
//---------------------------------------------------------------------------
void AMainClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//---------------------------------------------------------------------------
//	PRIVATE
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void AMainClass::StartGame()
{
    // Set the game state to starting
    AMainClass::SetGameState(MainUtilities::GameStateEnum::GAME_STARTING);

    // Spawn bp level streamer
    AMainClass::SpawnLevelStreamerActor();

    // Start Setting up the data bases for the world
    AMainClass::SetupDataBases();
}

//---------------------------------------------------------------------------
void AMainClass::EndGame(bool IsPlayerDead)
{
    if (IsPlayerDead)
    {
        // the player is dead, ask if the player want to try again
        AMainClass::SetGenerationState(MainUtilities::GenerationStepsEnum::GENERATING_FAILED);
        AMainClass::SetGameState(MainUtilities::GameStateEnum::GAME_FINISHED);
    }
    else
    {
        // Set the mode to an invalid state
        AMainClass::SetGenerationState(MainUtilities::GenerationStepsEnum::GENERATING_FAILED);
        AMainClass::SetGameState(MainUtilities::GameStateEnum::GAME_FAILED);

        // Log
        Log(MainUtilities::LogEnum::LOG_GENERATION_STATE, MainUtilities::GenerationTypeEnum::GAME_TYPE);
        Log(MainUtilities::LogEnum::LOG_GAME_STATE, MainUtilities::GenerationTypeEnum::GAME_TYPE);

        // Abort the game
        FGenericPlatformMisc::RequestExit(true);
    }
}

//---------------------------------------------------------------------------
void AMainClass::GenerateWorld()
{
    // Log
    AMainClass::SetGenerationState(MainUtilities::GenerationStepsEnum::GENERATING_STARTING);
    AMainClass::Log(MainUtilities::LogEnum::LOG_GENERATION_STATE, MainUtilities::GenerationTypeEnum::WORLD_TYPE);

    if (LevelStreamerClass->CreateStreamLevel())
    {
        AMainClass::SetGenerationState(MainUtilities::GenerationStepsEnum::GENERATING_COMPLETED);
        AMainClass::Log(MainUtilities::LogEnum::LOG_GENERATION_STATE, MainUtilities::GenerationTypeEnum::WORLD_TYPE);
    }
    else
    {
        // Abort the game since we might have some errors
        AMainClass::EndGame(false);
    }
}

//---------------------------------------------------------------------------
void AMainClass::SpawnLevelSystemIluminationActor()
{
    AMainClass::SetGenerationState(MainUtilities::GenerationStepsEnum::GENERATING_STARTING);
    AMainClass::Log(MainUtilities::LogEnum::LOG_GENERATION_STATE, MainUtilities::GenerationTypeEnum::ILUMINATION_TYPE);

    auto* levelSystemIluminationRef = OwningWorld->SpawnActor<AActor>(LevelSystemIluminationActor);

    if (levelSystemIluminationRef != NULL)
    {
        // cast the actor spawned to the correct class
        LevelSystemIlumination = static_cast<ALevelSystemIlumination*>(levelSystemIluminationRef);

        AMainClass::SetGenerationState(MainUtilities::GenerationStepsEnum::GENERATING_COMPLETED);
        AMainClass::Log(MainUtilities::LogEnum::LOG_GENERATION_STATE, MainUtilities::GenerationTypeEnum::ILUMINATION_TYPE);
    }
    else
    {
        // Abort the game since we might have some errors
        AMainClass::EndGame(false);
    }
}

//---------------------------------------------------------------------------
void AMainClass::SpawnPlayerCharacterActor()
{
    AMainClass::SetGenerationState(MainUtilities::GenerationStepsEnum::GENERATING_STARTING);
    AMainClass::Log(MainUtilities::LogEnum::LOG_GENERATION_STATE, MainUtilities::GenerationTypeEnum::PLAYER_TYPE);

    // Get the location to spawn the player from the level streamer class
    FVector playerSpawnlocation = LevelStreamerClass->PlayerLocationToSpawn;

    // Spawn parameters
    FActorSpawnParameters s;
    FRotator r = FRotator::ZeroRotator;

    // Spawn Player
    auto playerCharacterRef = OwningWorld->SpawnActor<AActor>(PlayerCharacterActor, playerSpawnlocation, r, s);
 
    if (playerCharacterRef != NULL)
    {
        // cast the actor spawned to the correct class
        PlayerCharacter = Cast<APlayerCharacter>(playerCharacterRef);

        AMainClass::SetGenerationState(MainUtilities::GenerationStepsEnum::GENERATING_COMPLETED);
        AMainClass::Log(MainUtilities::LogEnum::LOG_GENERATION_STATE, MainUtilities::GenerationTypeEnum::PLAYER_TYPE);
    }
    else
    {
        // Abort the game since we might have some errors
        AMainClass::EndGame(false);
    }
}

//---------------------------------------------------------------------------
void AMainClass::SpawnEnemyActor()
{
    AMainClass::SetGenerationState(MainUtilities::GenerationStepsEnum::GENERATING_STARTING);
    AMainClass::Log(MainUtilities::LogEnum::LOG_GENERATION_STATE, MainUtilities::GenerationTypeEnum::ENEMY_TYPE);
    
    // Get the location to spawn the enemy from the level streamer class
    FVector enemySpawnLocation = LevelStreamerClass->EnemyLocationToSpawn;

    // Spawn parameters
    FActorSpawnParameters s;
    FRotator r = FRotator::ZeroRotator;

    // Spawn Enemy
    auto EnemyCharacterRef = OwningWorld->SpawnActor<AActor>(EnemyCharacterActor, enemySpawnLocation, r, s);

    if (EnemyCharacterRef != NULL)
    {
        // cast the actor spawned to the correct class
        EnemyCharacter = Cast<AEnemyCharacter>(EnemyCharacterRef);

        AMainClass::SetGenerationState(MainUtilities::GenerationStepsEnum::GENERATING_COMPLETED);
        AMainClass::Log(MainUtilities::LogEnum::LOG_GENERATION_STATE, MainUtilities::GenerationTypeEnum::PLAYER_TYPE);
    }
    else
    {
        // Abort the game since we might have some errors
        AMainClass::EndGame(false);
    }

}

//---------------------------------------------------------------------------
void AMainClass::SpawnLevelStreamerActor()
{
    auto* levelStreamerRef = OwningWorld->SpawnActor<AActor>(LevelStreamerActor);

    if (levelStreamerRef != NULL)
    {
        // cast the actor spawned to the correct class
        LevelStreamerClass = static_cast<ALevelStreamerActor*>(levelStreamerRef);
    }
    else
    {
        // Abort the game since we might have some errors
        AMainClass::EndGame(false);
    }
}

//---------------------------------------------------------------------------
void AMainClass::SetupDataBases()
{
    // Set the Genration Step for the db merges
    AMainClass::SetGenerationState(MainUtilities::GenerationStepsEnum::GENERATING_STARTING);

    // Log
    AMainClass::Log(MainUtilities::LogEnum::LOG_GENERATION_STATE, MainUtilities::GenerationTypeEnum::DATABASE_TYPE);

    // Merge the data bases to know which map we need to load
    LevelStreamerClass->MergeDataTables();

    AMainClass::SetGenerationState(MainUtilities::GenerationStepsEnum::GENERATING_COMPLETED);
}

//---------------------------------------------------------------------------
// UTILITY
//---------------------------------------------------------------------------
void AMainClass::Log(MainUtilities::LogEnum logId, MainUtilities::GenerationTypeEnum type)
{
    switch (logId)
    {
    case MainUtilities::LogEnum::LOG_GAME_STATE:

        UE_LOG(LogTemp, Warning, TEXT("Game setup - Game State: %d"), GameState);

        break;
    case MainUtilities::LogEnum::LOG_GENERATION_STATE:

        UE_LOG(LogTemp, Warning, TEXT("Game setup - Generating State: %d, Generating type %d"), GenerationState, type);

        break;
    default:
        break;
    }
}



