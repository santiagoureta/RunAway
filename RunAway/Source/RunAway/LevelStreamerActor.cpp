// Copyright 2021 - 25/12/2021 - Santiago Ureta - RunAway

#include "LevelStreamerActor.h"
#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Controller.h"
#include "Main_Utilities.h"
#include "Engine/World.h"
#include "Engine/Engine.h"


//---------------------------------------------------------------------------
// Constructor
//---------------------------------------------------------------------------
ALevelStreamerActor::ALevelStreamerActor()
{
	// Load the data base LevelStreamerDataTable
	static ConstructorHelpers::FObjectFinder<UDataTable> LevelStreamerDataObject(TEXT("DataTable'/Game/BE/DataBases/LevelStremerData/LevelStreamer.LevelStreamer'"));
	if (LevelStreamerDataObject.Succeeded())
	{
		LevelStreamerDataTable = LevelStreamerDataObject.Object;
	}

	// Load the data base GraphLevelDataTable
	static ConstructorHelpers::FObjectFinder<UDataTable> GraphLevelDataObject(TEXT("DataTable'/Game/BE/DataBases/LevelStremerData/LevelGraph.LevelGraph'"));
	if (GraphLevelDataObject.Succeeded())
	{
		GraphLevelDataTable = GraphLevelDataObject.Object;
	}

	// Load the data base Level
	static ConstructorHelpers::FObjectFinder<UDataTable> LevelLightsDataObject(TEXT("DataTable'/Game/BE/DataBases/LevelStremerData/LevelLights.LevelLights'"));
	if (LevelLightsDataObject.Succeeded())
	{
		LevelLightsDataTable = LevelLightsDataObject.Object;
	}
}

//---------------------------------------------------------------------------
//	Begin Play
//---------------------------------------------------------------------------
void ALevelStreamerActor::BeginPlay()
{
	// Get the ref to out world we are in
	OwningWorld = GetWorld();

	// Game Starts
	Super::BeginPlay();
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Creates the graph for each level streamer that need to be loaded into the world
//---------------------------------------------------------------------------
bool ALevelStreamerActor::CreateStreamLevel()
{
	bool isSuccess = true;

	// Ref to out graph level object
	FGraphLevelObject* grapLevelObject;

	// init count of chunks to be loaded
	int count = 0;

	// loop throught the array of chunks we need to load
	do
	{
		// if we found the chunk inside our map we procede to load that chunk
		if (GraphLevelObjectMap.Find(count))
		{
			// Get the Ref of our object so we can manipulate the data
			grapLevelObject = GraphLevelObjectMap.Find(count);

			// Call the function to initialize the stream levels on the correct position
			LoadStreamLevel(grapLevelObject, count);

			count++;
		}
		else
		{
			// Log our failure case to notify that we are missing something in out data base
			UE_LOG(LogTemp, Warning, TEXT("Level Chunk Failed to load, its seems is missing from DB on id %d"), count);
			count++;
		}
	} while (count < GraphLevelObjectMap.Num());

	return isSuccess;
}

//---------------------------------------------------------------------------
// Load the values from the data tables to create the map
//---------------------------------------------------------------------------
void ALevelStreamerActor::MergeDataTables()
{
	if (LevelStreamerDataTable)
	{
		// Get a Random value from the table to load a level
		proceduralLevelId = 1; //FMath::RandRange(1, LevelStreamerDataTable->GetRowNames().Num());

		// Create context for the Find row parameter
		static const FString levelStreamerDataBasecontext(TEXT("LevelStreamerDataTable Context"));

		// Find the index inside the database and read the values
		FString rowNameToLoad = FString::Printf(TEXT("ProceduralLevel_%d"), proceduralLevelId);
		FLevelStreamerObject* LevelStreamerObject = LevelStreamerDataTable->FindRow<FLevelStreamerObject>(*rowNameToLoad, levelStreamerDataBasecontext, true);

		// Load the level graph related with the level id
		if (LevelStreamerObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("Level to Load:  %d"), proceduralLevelId);

			// Load all the information needed to define the size of the level
			LoadGraphSize(LevelStreamerObject);

			// If the table is loaded then we ask for the info
			if (GraphLevelDataTable)
			{
				// Load the information needed for each level chunk to then be proccesed
				LoadGraphLevelChunks();

				//Load the lights information needed for the level
				LoadLevelLightsInfo();
			}
		}
	}
}

//---------------------------------------------------------------------------
//	PRIVATE
//---------------------------------------------------------------------------
// Load the information needed for the level to manage the size of the graph
//---------------------------------------------------------------------------
void ALevelStreamerActor::LoadGraphSize(FLevelStreamerObject* LevelStreamerObject)
{
	// Set the initial values for the graph and tile size
	GraphSize = LevelStreamerObject->GraphSize;
	TileSize = LevelStreamerObject->TilesSize;
}

//---------------------------------------------------------------------------
// Load the information needed for each level chunk to then be proccesed
//---------------------------------------------------------------------------
void ALevelStreamerActor::LoadGraphLevelChunks()
{
	// Create context for the Find row parameter
	static const FString graphLevelDataBasecontext(TEXT("GraphLevelDataTable Context"));

	// Get the list of indexis
	TArray<FName> listOfRows = GraphLevelDataTable->GetRowNames();

	// grapObject ref
	FGraphLevelObject* graphObject;

	// Check the part of the map that will be loaded
	for (int i = 0; i < listOfRows.Num(); i++)
	{
		// Key of the row id
		FString RowKeyId = listOfRows[i].ToString();

		// We found our row
		graphObject = GraphLevelDataTable->FindRow<FGraphLevelObject>(*RowKeyId, graphLevelDataBasecontext, true);

		// check that are the correct ones for our selected level id
		if (graphObject->ProceduralLevelId == proceduralLevelId)
		{
			// Log
			UE_LOG(LogTemp, Warning, TEXT("Level part added %s"), *graphObject->LevelName);

			// Create the map with the custom stream levels
			GraphLevelObjectMap.Add(i, *graphObject);
		}
	}

	// Log
	UE_LOG(LogTemp, Warning, TEXT("Total size of parts to load %d"), GraphLevelObjectMap.Num());
}

//---------------------------------------------------------------------------
// Load the lights information needed for the level
//---------------------------------------------------------------------------
void ALevelStreamerActor::LoadLevelLightsInfo()
{
	// Load the lights data base values
	if (LevelLightsDataTable)
	{
		// Create context for the Find row parameter
		static const FString LevelLightsDataBasecontext(TEXT("LevelLightsDataTable Context"));

		// Get the list of indexis
		TArray<FName> LevelLightsRows = LevelLightsDataTable->GetRowNames();

		// light object ref
		FLevelLightStruct* lightObject;

		// iter trought the database
		for (int i = 0; i < LevelLightsRows.Num(); i++)
		{
			// Key of the row id
			FString RowKeyId = LevelLightsRows[i].ToString();

			// We found our row
			lightObject = LevelLightsDataTable->FindRow<FLevelLightStruct>(*RowKeyId, LevelLightsDataBasecontext, true);

			LevelLightsObjectMap.Add(i, *lightObject);
		}
	}
}

//---------------------------------------------------------------------------
// Load each stream level into out level graph
//---------------------------------------------------------------------------
void ALevelStreamerActor::LoadStreamLevel(FGraphLevelObject* graphLevelRef, int count)
{
	FString levelToLoad = *graphLevelRef->LevelName;

	int index_X = graphLevelRef->Index_X;
	int index_Y = graphLevelRef->Index_Y;

	float rotation_X = graphLevelRef->Rotation_X;
	float rotation_Y = graphLevelRef->Rotation_Y;
	float rotation_Z = graphLevelRef->Rotation_Z;

	// The information of our level we want to load
	ULevelStreaming* level = UGameplayStatics::GetStreamingLevel(OwningWorld, *levelToLoad);

	if (level)
	{
		// Create the name instance
		FString nameInstance = FString::Printf(TEXT("%s_%d_x_%d_y"), *levelToLoad, index_X, index_Y);

		ULevelStreaming* levelRef = level->CreateInstance(nameInstance);

		UGameplayStatics::UnloadStreamLevel(OwningWorld, *levelToLoad, FLatentActionInfo(), true);

		// Set the new position and rotation
		int NewPosition_X = (GraphSize * index_X) * (TileSize / 2);
		int NewPosition_Y = (GraphSize * index_Y) * (TileSize / 2);

		// Create the new rotation and get the direction
		const FRotator YawRotation(rotation_X, rotation_Y, rotation_Z);
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Vector that stores the new position
		FVector position;
		position.Set(NewPosition_X, NewPosition_Y, 0);

		// Transform the position for the instance
		FTransform newTransform;
		newTransform.SetToRelativeTransform(levelRef->LevelTransform);
		newTransform.SetRotation(Direction.ToOrientationQuat());
		newTransform.SetLocation(position);

		// Log the instance been loaded, the position on the map and the value of the index i, j
		UE_LOG(LogTemp, Warning, TEXT("Instance name: %s , Position: %f on X, %f on Y, %f on Z, Index_X : %d , Index_Y : %d"), *nameInstance, position.X, position.Y, position.Z, index_X, index_Y);

		//Assign a new transform to our level
		levelRef->LevelTransform = newTransform;

		UE_LOG(LogTemp, Warning, TEXT("New Location: %s"), *levelRef->LevelTransform.GetLocation().ToString());

		int chunkLightTypeId = graphLevelRef->LightTypeId;

		// check the level type to know if we need to add a light here
		if (chunkLightTypeId != MainUtilities::LevelLightTypeEnum::LEVEL_LIGHT_TYPE_INVALID)
		{
			// TODO-SURETA: add the new light system here

			//Asystem = NewObject<AIluminationSystem>(AIluminationSystem::StaticClass());

			//// Fill the object values
			//Asystem->SetLevelChunkType(chunkLightTypeId);
			//Asystem->SetLevelChunkDirection(Direction);
			//Asystem->SetLevelChunkPosition(position);

			//Asystem->SetLevelLightsCount(2);

			//// add to the list the number of lights we need to spawn on the game (this will be manage by the LevelIluminationSystem)
			//LightObjectList.Add(Asystem);
		}

		// Load the stream level
		FLatentActionInfo info;
		info.UUID = count;

		// Load the level with all the information that we have setted
		UGameplayStatics::LoadStreamLevel(OwningWorld, *nameInstance, true, true, info);
	}
	else
	{
		// probably the name of the level we are currently loading is missing or isnt created
		UE_LOG(LogTemp, Warning, TEXT("Failed to load the: %s level name or this is intentionally"), *levelToLoad);
	}
}
