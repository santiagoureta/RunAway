// Copyright 2021 - 25/12/2021 - Santiago Ureta - RunAway

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Misc/EnumRange.h"
#include "Engine/DataTable.h"
#include "Main_Utilities.h"
#include "IluminationSystem.h"
#include "LevelStreamerActor.generated.h"

USTRUCT(BlueprintType)
struct FLevelStreamerObject : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ProceduralLevelId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 GraphSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 TilesSize;
};

USTRUCT(BlueprintType)
struct FGraphLevelObject : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ProceduralLevelId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Index_X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Index_Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Rotation_X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Rotation_Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Rotation_Z;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 LevelType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 LightTypeId;
};

USTRUCT(BlueprintType)
struct FLevelLightStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LightTypeId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumOfLights;
};

class AIluminationSystem;

UCLASS()
class RUNAWAY_API ALevelStreamerActor : public AActor
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	ALevelStreamerActor();

	// Called when the game starts to create the stream level
	virtual bool CreateStreamLevel();

	// Utility function to merge the data bases to create the map
	virtual void MergeDataTables();

	TArray<AIluminationSystem*> GetLightsListToAdd() { return LightObjectList; };
	
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	// Utility function to merge the data bases to create the map
	virtual void LoadGraphSize(FLevelStreamerObject* LevelStreamerObject);

	// Utility function to merge the data bases to create the map
	virtual void LoadGraphLevelChunks();

	// Utility function to merge the data bases to create the map
	virtual void LoadLevelLightsInfo();

	// Utility function to Load each stream level to the graph
	virtual void LoadStreamLevel(FGraphLevelObject* graphLevelRef, int count);

	// Property to read values from the level streamer data base
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataBase, meta = (AllowPrivateAccess = "true"))
		class UDataTable* LevelStreamerDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataBase, meta = (AllowPrivateAccess = "true"))
		class UDataTable* GraphLevelDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataBase, meta = (AllowPrivateAccess = "true"))
		class UDataTable* LevelLightsDataTable;

	// Map that has the chunk of levels to be loaded
	TMap<int, FGraphLevelObject> GraphLevelObjectMap;

	// Map that has the light information
	TMap<int, FLevelLightStruct> LevelLightsObjectMap;

	// Map with the level chunks were we need to load
	TArray<AIluminationSystem*> LightObjectList;

	// AIluminationSystem ref
	AIluminationSystem* Asystem;

	// WorldRef
	UWorld* OwningWorld;

	// Graph size
	int GraphSize = 0;

	// Tile size
	float TileSize = 0;

	// Level id to be loaded
	int proceduralLevelId = -1;

};
