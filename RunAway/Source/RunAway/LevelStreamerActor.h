// Copyright 2021 - 25/12/2021 - Santiago Ureta - RunAway

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Misc/EnumRange.h"
#include "Engine/DataTable.h"
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
};

UCLASS()
class RUNAWAY_API ALevelStreamerActor : public AActor
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	ALevelStreamerActor();

	enum LevelTypeEnum
	{
		LEVEL_TYPE_INVALID = -1,
		LEVEL_TYPE_HOUSE = 0,
		LEVEL_TYPE_STREET = 1,
		LEVEL_TYPE_STREET_CORNER = 2,
		LEVEL_TYPE_GRASS = 3,
		LEVEL_TYPE_PARK = 4,
		LEVEL_TYPE_GAS_STATION = 5,
		LEVEL_TYPE_APARTMENT = 6,
		LEVEL_TYPE_FOOD_PLACES = 7,
		LEVEL_TYPE_PASSAGE = 8,

		LEVEL_TYPE_NUM = LEVEL_TYPE_PASSAGE
	};


	// Called when the game starts to create the stream level
	virtual bool CreateStreamLevel();

	// Utility function to merge the data bases to create the map
	virtual void MergeDataTables();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	// Property to read values from the level streamer data base
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataBase, meta = (AllowPrivateAccess = "true"))
		class UDataTable* LevelStreamerDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataBase, meta = (AllowPrivateAccess = "true"))
		class UDataTable* GraphLevelDataTable;

	// Map with the chunk of levels to be loaded
	TMap<int, FGraphLevelObject> GraphLevelObjectMap;

	// Map with the level chunks were we need to load
	TArray<FString> LightList;

	// WorldRef
	UWorld* OwningWorld;

	// Graph size
	int GraphSize = 0;

	// Tile size
	float TileSize = 0;

	// Utility function to Load each stream level to the graph
	virtual void LoadStreamLevel(FName levelToLoad, int count, int index_X, int index_Y, float rotation_X, float rotation_Y, float rotation_Z, int levelType);
};
