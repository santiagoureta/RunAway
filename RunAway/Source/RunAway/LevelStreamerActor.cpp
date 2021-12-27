// Copyright 2021 - 25/12/2021 - Santiago Ureta - RunAway


#include "LevelStreamerActor.h"

#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
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
//	Tick
//---------------------------------------------------------------------------
void ALevelStreamerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//---------------------------------------------------------------------------
//	Begin Play
//---------------------------------------------------------------------------
void ALevelStreamerActor::BeginPlay()
{
	OwningWorld = GetWorld();

	// Game Starts
	Super::BeginPlay();

	// Create Graph wih the custom filter list
	ALevelStreamerActor::CreateGraph(GraphSize, FilterMap);

	// Create the map with the custom stream levels
	ALevelStreamerActor::CreateStreamLevel(GraphSize, LevelToLoad, TileSize);
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

}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Load the values from the data tables to create the map
//---------------------------------------------------------------------------
void ALevelStreamerActor::MergeDataTables()
{
	if (LevelStreamerDataTable)
	{		
		int proceduralLevelId = FMath::RandRange(0, 4);
		static const FString context(TEXT("LevelStreamerObject Context"));
		FString rowNameToLoad = FString::Printf(TEXT("ProceduralLevel_%d"), proceduralLevelId);

		FLevelStreamerObject* LevelStreamerObject = LevelStreamerDataTable->FindRow<FLevelStreamerObject>(*rowNameToLoad, context, true);

		if (LevelStreamerObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("Level Loaded:  %d"), LevelStreamerObject->ProceduralLevelId);
		}
	}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Creates the map with the custom graph
//---------------------------------------------------------------------------
void ALevelStreamerActor::CreateStreamLevel(int graphSize, FName levelToLoad, float tileSize)
{
	int count = 0;
	for (size_t i = 0; i < graphSize; i++)
	{
		for (size_t j = 0; j < graphSize; j++)
		{
			// Call the function to initialize the stream levels on the correct position
			LoadStreamLevel(levelToLoad, count, i , j);

			// count the number of Levels been loaded
			count++;

			// Check out last case
			if (count == graphSize * graphSize)
			{
				// Call the function to initialize the stream levels on the correct position
				LoadStreamLevel(levelToLoad, count, i, j);
			}
		}
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Creates the custom graph with the filter list
//---------------------------------------------------------------------------
void ALevelStreamerActor::LoadStreamLevel(FName levelToLoad, int count, int index_X, int index_Y)
{
	ULevelStreaming* level = UGameplayStatics::GetStreamingLevel(OwningWorld, levelToLoad);

	//Create the name instance
	FString nameInstance = FString::Printf(TEXT("%s_%d"), *LevelToLoad.ToString(), count);

	// Set the new position
	int NewPosition_X = (GraphSize * index_X) * (TileSize / 2);
	int NewPosition_Y = (GraphSize * index_Y) * (TileSize / 2);

	FVector position;
	position.Set(NewPosition_X, NewPosition_Y, 0);

	// Log the instance been loaded, the position on the map and the value of the index i, j
	UE_LOG(LogTemp, Warning, TEXT("Instance name: %s , Position: %f on X, %f on Y, %f on Z, Index_X : %d , Index_Y : %d "), *nameInstance, position.X, position.Y, position.Z, index_X, index_Y);

	// Transform the position for the instance
	FTransform newTransform;
	newTransform.SetTranslation(position);

	// Create instance of streaming level
	level->CreateInstance(nameInstance);

	//Assign a new transform to our level
	level->LevelTransform = newTransform;

	// Load the stream level
	FLatentActionInfo info;
	info.UUID = count;

	UGameplayStatics::LoadStreamLevel(OwningWorld, *nameInstance, true, false, info);
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Creates the custom graph with the filter list
//---------------------------------------------------------------------------
void ALevelStreamerActor::CreateGraph(int graphSize, TMap<int32, FString> filterMap)
{
	for (size_t i = 0; i < graphSize; i++)
	{
		for (size_t j = 0; j < graphSize; j++)
		{

		}
	}
}