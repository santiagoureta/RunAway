// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "Engine/DataTable.h"
#include "LightObject.h"
#include "LightSpawnActor.generated.h"

USTRUCT(BlueprintType)
struct FLevelLightStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 LightTypeId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LightPosition_X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LightPosition_Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LightPosition_Z;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LightRotation_X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LightRotation_Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LightRotation_Z;
};

UENUM(BlueprintType)
enum class LevelLightType : uint8 {
	STREET = 0 UMETA(DisplayName = "STREET"),
	STREET_CORNER = 1  UMETA(DisplayName = "STREET_CORNER")
};

UCLASS()
class RUNAWAY_API ALightSpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ALightSpawnActor();

	//! Function that starts spawning the lights
	UFUNCTION(BlueprintImplementableEvent, Category = "LightSpawnActor")
		void StartSpawningLights(ALevelSystemIlumination* levelSystemRef);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	// Utility function to merge the lights information needed for the level
	virtual void LoadLevelLightsInfo();

	// Box component Ref
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BoxComponent, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* CollisionMesh;

	// Arrow component Ref
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BoxComponent, meta = (AllowPrivateAccess = "true"))
		UArrowComponent* Arrow;

	//! static mesh component ref
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LightInfo, meta = (AllowPrivateAccess = "true"))
		UStaticMesh* SpawnLightMesh;

	//! world scale value for each light
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LightInfo, meta = (AllowPrivateAccess = "true"))
		float LightWorldScale = 1.25f;

	// Property to read values from the level streamer data base
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LightInfo, meta = (AllowPrivateAccess = "true"))
		LevelLightType LightTypeEnum;

	// level light info data base
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataBase, meta = (AllowPrivateAccess = "true"))
		class UDataTable* LevelLightsDataTable;

	// Map that has the light information
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelLightMap, meta = (AllowPrivateAccess = "true"))
		TMap<LevelLightType, FLevelLightStruct> LevelLightsObjectMap;
	
};
