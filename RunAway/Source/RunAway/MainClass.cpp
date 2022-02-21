// Fill out your copyright notice in the Description page of Project Settings.


#include "MainClass.h"
#include "LevelStreamerActor.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

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

    // Get the ref of the spawned level streamer
    LevelStreamerClass = OwningWorld->SpawnActor<ALevelStreamerActor>();

	Super::BeginPlay();
	
    UE_LOG(LogTemp, Warning, TEXT("Game setup - Game mode state: %d"), GameState);

    
    // Start the game
    AMainClass::StartGame();
       
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

    // Log
    UE_LOG(LogTemp, Warning, TEXT("Game setup - Game mode state: %d"), GameState);

    // Start Setting up the data bases for the world
    AMainClass::SetupDataBases();

    AMainClass::GenerateWorld();
}

//---------------------------------------------------------------------------
void AMainClass::SetupDataBases()
{
    // Set the Genration Step for the db merges
    AMainClass::SetGenerationState(MainUtilities::GenerationStepsEnum::GENERATING_STARTING);

    // Log
    UE_LOG(LogTemp, Warning, TEXT("Game setup - Generating Db: %d"), GenerationState);

    if (LevelStreamerClass != NULL)
    {
        // Merge the data bases to know which map we need to load
        LevelStreamerClass->MergeDataTables();

        AMainClass::SetGenerationState(MainUtilities::GenerationStepsEnum::GENERATING_COMPLETED);
    }
    else
    {
        // Set the mode to an invalid state
        AMainClass::SetGenerationState(MainUtilities::GenerationStepsEnum::GENERATING_FAILED);
        AMainClass::SetGameState(MainUtilities::GameStateEnum::GAME_FAILED);
    }

    // Log
    UE_LOG(LogTemp, Warning, TEXT("Game setup - Generating Db: %d"), GenerationState);
}

//---------------------------------------------------------------------------
void AMainClass::GenerateWorld()
{
    if (LevelStreamerClass->CreateStreamLevel())
    {
        //TODO Generate Lights system, Enemy and player
        AMainClass::SetGameState(MainUtilities::GameStateEnum::GAME_READY);

        // Log
        UE_LOG(LogTemp, Warning, TEXT("Game setup - Game mode state: %d"), GameState);
    }
}

//---------------------------------------------------------------------------
void AMainClass::EndGame()
{
    //TODO:
}

