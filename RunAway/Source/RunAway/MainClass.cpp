// Fill out your copyright notice in the Description page of Project Settings.


#include "MainClass.h"
#include "LevelStreamerActor.h"
#include "UObject/ConstructorHelpers.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "LevelSystemIlumination.h"
#include "PlayerCharacter.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

AMainClass::AMainClass()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMainClass::BeginPlay()
{
    // Get the Ref of the world
    OwningWorld = GetWorld();

    // Start the game
    AMainClass::StartGame();

    Super::BeginPlay();
}

// Called every frame
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

    // Generating world
    AMainClass::GenerateWorld();
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
void AMainClass::GenerateWorld()
{
    // Log
    AMainClass::SetGenerationState(MainUtilities::GenerationStepsEnum::GENERATING_STARTING);
    AMainClass::Log(MainUtilities::LogEnum::LOG_GENERATION_STATE, MainUtilities::GenerationTypeEnum::WORLD_TYPE);

    if (LevelStreamerClass->CreateStreamLevel())
    {
        AMainClass::SetGenerationState(MainUtilities::GenerationStepsEnum::GENERATING_COMPLETED);
        AMainClass::Log(MainUtilities::LogEnum::LOG_GENERATION_STATE, MainUtilities::GenerationTypeEnum::WORLD_TYPE);

        // TODO: for the enemy and the player we need to get the values from the map inside the levelstreamer

        //Spawn the bp for the player character
        AMainClass::SpawnPlayerCharacterActor();

        //Spawn the bp for the enemy
        AMainClass::SpawnEnemyActor();

        // Spawn the bp level system ilumination actor
        AMainClass::SpawnLevelSystemIluminationActor();
    }
    else
    {
        // Abort the game since we might have some errors
        AMainClass::EndGame(false);
    }
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

    FActorSpawnParameters s;

    // TODO: Retrieve the const from the level streamer to spawn the player on the correct position
    FVector v(0, 800, 22);
    FRotator r = FRotator::ZeroRotator;

    auto* playerCharacterRef = OwningWorld->SpawnActor<AActor>(PlayerCharacterActor, v, r, s);

    if (playerCharacterRef != NULL)
    {
        // cast the actor spawned to the correct class
        PlayerCharacter = static_cast<APlayerCharacter*>(playerCharacterRef);

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

    // TODO Spawn the enemy
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



