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

	//!
	virtual void LightActionImpl(LightAction LightActionId);
	
	//!
	virtual void EnemyDebuffImpl(EnemyDebuff DebuffId);
	
	//!
	ALightObject* LightObject;
	
	//!
	AEnemyCharacter* EnemyObject;
};
