// Fill out your copyright notice in the Description page of Project Settings.


#include "MainClass.h"
#include "LevelStreamerActor.h"
#include "UObject/ConstructorHelpers.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "LevelSystemIlumination.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMainClass::AMainClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMainClass::BeginPlay()
{
    // Get the Ref of the world
    OwningWorld = GetWorld();

    // Spawn level streamer
    LevelStreamerClass = OwningWorld->SpawnActor<ALevelStreamerActor>();

    Super::BeginPlay();

    if (LevelStreamerClass != NULL)
    {
        // Start the game
        AMainClass::StartGame();
    }
    else
    {
        // Abort the game since we might have some errors
        AMainClass::EndGame(false);
    }
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

    if (LevelStreamerClass != NULL)
    {
        // Log
        AMainClass::Log(MainUtilities::LogEnum::LOG_GENERATION_STATE, MainUtilities::GenerationTypeEnum::DATABASE_TYPE);

        // Merge the data bases to know which map we need to load
        LevelStreamerClass->MergeDataTables();

        AMainClass::SetGenerationState(MainUtilities::GenerationStepsEnum::GENERATING_COMPLETED);
    }
    else
    {
        // Abort the game since we might have some errors
        AMainClass::EndGame(false);
    }
}

//---------------------------------------------------------------------------
void AMainClass::GenerateWorld()
{
    if (LevelStreamerClass->CreateStreamLevel())
    {
        // Log
        AMainClass::SetGenerationState(MainUtilities::GenerationStepsEnum::GENERATING_STARTING);
        AMainClass::Log(MainUtilities::LogEnum::LOG_GENERATION_STATE, MainUtilities::GenerationTypeEnum::WORLD_TYPE);

        //TODO - SURETA: Continue working on the lights system, work with the levelStreamerActor
        // Get the light object list to know where we need to spawn the lights with their information
        auto LightObjectList = LevelStreamerClass->GetLightsListToAdd();

        // Spawn level ilumination system
        LevelSystemIlumination = OwningWorld->SpawnActor<ALevelSystemIlumination>();
        if (LevelSystemIlumination != NULL)
        {
            AMainClass::SetGenerationState(MainUtilities::GenerationStepsEnum::GENERATING_COMPLETED);
            if (LevelSystemIlumination->CreateLightSystem(LightObjectList))
            {
                // Log
                AMainClass::SetGenerationState(MainUtilities::GenerationStepsEnum::GENERATING_STARTING);
                AMainClass::Log(MainUtilities::LogEnum::LOG_GENERATION_STATE, MainUtilities::GenerationTypeEnum::ILUMINATION_TYPE);
            }
            else
            {
                // Set the mode to an invalid state
                AMainClass::SetGenerationState(MainUtilities::GenerationStepsEnum::GENERATING_FAILED);
                AMainClass::SetGameState(MainUtilities::GameStateEnum::GAME_FAILED);

                // Abort the game since we might have some errors
                AMainClass::EndGame(false);
            }
        }
    }
    else
    {
        // Set the mode to an invalid state
        AMainClass::SetGenerationState(MainUtilities::GenerationStepsEnum::GENERATING_FAILED);
        AMainClass::SetGameState(MainUtilities::GameStateEnum::GAME_FAILED);

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



