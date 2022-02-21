// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IluminationSystem.generated.h"

USTRUCT(BlueprintType)
struct FLightObject
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 LightId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LightPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsOn;
};

UCLASS()
class RUNAWAY_API AIluminationSystem : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AIluminationSystem();

	//! Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIluminationSystem::meshComponent")
		class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIluminationSystem::LightComponent")
		class USpotLightComponent* LightComponent;

		class UStaticMesh* Mesh;

protected:

	//! Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	//! LightMap that has all the lights spawned on the map.
	TMap<int, FLightObject> LightMap;

};
