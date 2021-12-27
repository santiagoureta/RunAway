// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"

#include "LevelStreamerActor.generated.h"

USTRUCT(BlueprintType)
struct FLevelStreamerObject : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ProceduralLevelId;
};

UCLASS()
class RUNAWAY_API ALevelStreamerActor : public AActor
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	ALevelStreamerActor();

	// Graph size
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int GraphSize = 0;

	// Tile size
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TileSize = 0;

	// MapToLoad
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName LevelToLoad;

	// FilterList
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int32, FString> FilterMap;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	// Property to read values from the level streamer data base
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataBase, meta = (AllowPrivateAccess = "true"))
		class UDataTable* LevelStreamerDataTable;

	// CustomGraph
	TMap<int32, FString> CustomGraph;

	// WorldRef
	UWorld* OwningWorld;

	// Called when the game starts to create the stream level
	virtual void CreateStreamLevel(int graphSize, FName levelToLoad, float tileSize);

	// Utility function to create the custom graph
	virtual void CreateGraph(int graphSize, TMap<int32, FString> filterMap);

	// Utility function to load the data base to create the map
	virtual void LoadDataTables();

	// Utility function to merge the data bases to create the map
	virtual void MergeDataTables();

	// Utility function to Load each stream level to the graph
	virtual void LoadStreamLevel(FName levelToLoad, int count, int index_X, int index_Y);
};
