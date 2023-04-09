// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelSystemIlumination.generated.h"

class AEnemyCharacter;
class ALightObject;

UENUM(BlueprintType)
enum class EnemyDebuff : uint8 
{
	SLOWED = 0 UMETA(DisplayName = "SLOWED"),
	STUN = 1  UMETA(DisplayName = "STUN"),
	TELEPORT = 2 UMETA(DisplayName = "TELEPORT")
};

UENUM(BlueprintType)
enum class DebuffPack : uint8
{
	SLOWED_FLICKER = 0 UMETA(DisplayName = "SLOWED_FLICKER"),
	STUN_EXPLOTE = 1  UMETA(DisplayName = "STUN_EXPLOTE"),
	DELAY_EXPLOTE = 2 UMETA(DisplayName = "DELAY_EXPLOTE"),
	DELAY_SLOWED = 3 UMETA(DisplayName = "DELAY_SLOWED")
};

UENUM(BlueprintType)
enum class LightAction : uint8
{
	FLICKER = 0 UMETA(DisplayName = "FLICKER"),
	EXPLOTE = 1  UMETA(DisplayName = "EXPLOTE"),
	DELAY_EXPLOTE = 2 UMETA(DisplayName = "DELAY_EXPLOTE"),
	DELAY_SLOWED = 3 UMETA(DisplayName = "DELAY_SLOWED")
};

UCLASS()
class RUNAWAY_API ALevelSystemIlumination : public AActor
{
	GENERATED_BODY()
	
public:	

	//! Constructor
	ALevelSystemIlumination();

	//! Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//! Function that triggers debuffs on the enemy
	UFUNCTION(BlueprintCallable, Category = "Enemy")
		virtual void EnemyOnLight(UObject* LightRef, UObject* EnemyRef);
	
	//! Function that Notifies the light system the player has gone trough a light
	UFUNCTION(BlueprintCallable, Category = "Player")
		virtual void PlayerOnLight(UObject* LightRef);
	
	//! Function that Notifies the light system the player has gone out of a light
	UFUNCTION(BlueprintCallable, Category = "Player")
		virtual void PlayerOffLight(UObject* LightRef);

protected:

	//! Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:

	//! Function that Retrieves the list of lights on the level
	UFUNCTION(BlueprintCallable, Category = "LightSystem")
		virtual void StartShutDown();

	//! Function that Renders the lights on the level
	UFUNCTION(BlueprintCallable, Category = "LightSystem")
		virtual void RenderLights();

	//! Function that Retrieves the list of lights on the level
	UFUNCTION(BlueprintCallable, Category = "LightSystem")
		virtual void SetLightList();

	//! Function that set the action each light will do
	virtual void SetLightAction(LightAction LightActionId);
	
	//! Function that sets the debuff for the enemy each time
	virtual void SetEnemyDebuff(EnemyDebuff DebuffId);

	//! WorldRef
	UWorld* OwningWorld;

	//! Light object Ref
	ALightObject* LightObject;

	//! Enemy object Ref
	AEnemyCharacter* EnemyObject;

	//! Map of lights that had seen the actor
	TMap<FString, ALightObject*> mLightWatched;

	//! LightList on the world
	TArray<ALightObject*> lightList;

	//! counter for the logic to determinated the end of the shutdown
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LightInfo, meta = (AllowPrivateAccess = "true"))
		int lightsOffCount = 0;

	//! Delay for the system to let the light flicker
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LightInfo, meta = (AllowPrivateAccess = "true"))
		float delayValue = 10.0f;
	
};
