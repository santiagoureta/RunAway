// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelSystemIlumination.generated.h"

UCLASS()
class RUNAWAY_API ALevelSystemIlumination : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ALevelSystemIlumination();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IluminationSystemReady();

	//
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> OverlapActor;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:

	virtual void GetNearLights();

	//! flag to return
	bool isSystemReady;

	// Player Character Ref
	class APlayerCharacter* PlayerCharacter;
};
