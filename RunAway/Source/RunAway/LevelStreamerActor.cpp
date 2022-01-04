// Copyright 2021 - 25/12/2021 - Santiago Ureta - RunAway

#include "LevelStreamerActor.h"
#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "Engine/Engine.h"


//---------------------------------------------------------------------------
// Constructor
//---------------------------------------------------------------------------
ALevelStreamerActor::ALevelStreamerActor()
{
	// Load all the tables we need for the data merging
	ALevelStreamerActor::LoadDataTables();

	// then we need to merge the values to retrieve all the information
	ALevelStreamerActor::MergeDataTables();
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

	// Create the stream level with out info
	ALevelStreamerActor::CreateStreamLevel(GraphSize, GraphLevelObject, TileSize);
}

//---------------------------------------------------------------------------
//	PRIVATE
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Load the values from the data tables to create the map
//---------------------------------------------------------------------------
void ALevelStreamerActor::LoadDataTables()
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
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Load the values from the data tables to create the map
//---------------------------------------------------------------------------
void ALevelStreamerActor::MergeDataTables()
{
	if (LevelStreamerDataTable)
	{	
		// Get a Random value from the table to load a level
		int proceduralLevelId = 1; //FMath::RandRange(1, LevelStreamerDataTable->GetRowNames().Num());

		// Create context for the Find row parameter
		static const FString levelStreamerDataBasecontext(TEXT("LevelStreamerDataTable Context"));

		// Find the index inside the database and read the values
		FString rowNameToLoad = FString::Printf(TEXT("ProceduralLevel_%d"), proceduralLevelId);
		FLevelStreamerObject* LevelStreamerObject = LevelStreamerDataTable->FindRow<FLevelStreamerObject>(*rowNameToLoad, levelStreamerDataBasecontext, true);

		// Load the level graph related with the level id
		if (LevelStreamerObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("Level to Load:  %d"), proceduralLevelId);

			// Set the initial values for the graph and tile size
			GraphSize = LevelStreamerObject->GraphSize;
			TileSize = LevelStreamerObject->TilesSize;

			// If the table is loaded then we ask for the info
			if (GraphLevelDataTable)
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
						GraphLevelObject.Add(i, *graphObject);
					}
				}
				// Log
				UE_LOG(LogTemp, Warning, TEXT("Total size of parts to load %d"), GraphLevelObject.Num());
			}
		}
	}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Creates the graph for each level streamer that need to be loaded into the world
//---------------------------------------------------------------------------
void ALevelStreamerActor::CreateStreamLevel(int graphSize, TMap<int, FGraphLevelObject>& levelChunkMap, float tileSize)
{
	// Ref to out graph level object
	FGraphLevelObject* grapLevelObject;

	// init count of chunks to be loaded
	int count = 0;

	// loop throught the array of chunks we need to load
	do
	{
		// if we found the chunk inside our map we procede to load that chunk
		if (levelChunkMap.Find(count))
		{
			// Get the Ref of our object so we can manipulate the data
			grapLevelObject = levelChunkMap.Find(count);

			// Call the function to initialize the stream levels on the correct position
			LoadStreamLevel(*grapLevelObject->LevelName, count, grapLevelObject->Index_X, grapLevelObject->Index_Y, grapLevelObject->Rotation_X, grapLevelObject->Rotation_Y, grapLevelObject->Rotation_Z);
			count++;
		}
		else
		{
			// Log our failure case to notify that we are missing something in out data base
			UE_LOG(LogTemp, Warning, TEXT("Level Chunk Failed to load, its seems is missing from DB on id %d"), count);
			count++;
		}
	} while (count < levelChunkMap.Num());
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Load each stream level into out level graph
//---------------------------------------------------------------------------
void ALevelStreamerActor::LoadStreamLevel(FName levelToLoad, int count, int index_X, int index_Y, float rotation_X, float rotation_Y, float rotation_Z)
{
	// The information of our level we want to load
	ULevelStreaming* level = UGameplayStatics::GetStreamingLevel(OwningWorld, levelToLoad);

	if (level)
	{
		// Create the name instance
		FString nameInstance = FString::Printf(TEXT("%s_%d_x_%d_y"), *levelToLoad.ToString(), index_X, index_Y);

		ULevelStreaming* levelRef = level->CreateInstance(nameInstance);

		UGameplayStatics::UnloadStreamLevel(OwningWorld, levelToLoad, FLatentActionInfo(), true);

		// Set the new position and rotation
		int NewPosition_X = (GraphSize * index_X) * (TileSize / 2);
		int NewPosition_Y = (GraphSize * index_Y) * (TileSize / 2);

		// Create the new rotation and get the direction
		const FRotator YawRotation(rotation_X, rotation_Y, rotation_Z);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

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

		// Load the stream level
		FLatentActionInfo info;
		info.UUID = count;

		UGameplayStatics::LoadStreamLevel(OwningWorld, *nameInstance, true, false, info);
	}
	else
	{
		// probably the name of the level we are currently loading is missing or isnt created
		UE_LOG(LogTemp, Warning, TEXT("Failed to load the: %s level name or this is intentionally"), *levelToLoad.ToString());
	}
}