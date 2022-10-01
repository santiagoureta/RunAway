// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSystemIlumination.h"
#include "LightObject.h"
#include "PlayerCharacter.h"
#include "EnemyCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"

ALevelSystemIlumination::ALevelSystemIlumination()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALevelSystemIlumination::BeginPlay()
{
	Super::BeginPlay();
}

//---------------------------------------------------------------------------
void ALevelSystemIlumination::LightActionImpl(LightAction LightActionId)
{
	// this should not occur at this point
	if (LightObject != NULL) 
	{
		switch (LightActionId)
		{
			case LightAction::FLICKER:
				LightObject->FlickeringLight();
				break;

			case LightAction::EXPLOTE:
				LightObject->LightToExplote();
				break;

			case LightAction::DELAY_EXPLOTE:
				LightObject->LightToExploteWithDelay();
				break;

			case LightAction::DELAY_SLOWED:
				/*LightObject->LighToExploteWithDelay();*/
				break;

			default:
				break;
		}
	}
}

//---------------------------------------------------------------------------
void ALevelSystemIlumination::EnemyDebuffImpl(EnemyDebuff DebuffId)
{
	//// this should not occur at this point
	if (EnemyObject != NULL)
	{
		switch (DebuffId)
		{
			case EnemyDebuff::SLOWED:
				EnemyObject->SlowEnemy();
				break;
			
			case EnemyDebuff::STUN:
				EnemyObject->StunEnemy();
				break;

			default:
			break;
		}
	}
}

//---------------------------------------------------------------------------
// Called every frame
//---------------------------------------------------------------------------
void ALevelSystemIlumination::Tick(float DeltaTime)
{	
	Super::Tick(DeltaTime);
}

//---------------------------------------------------------------------------
void ALevelSystemIlumination::EnemyOnLight(UObject* LightRef, UObject* EnemyRef)
{
	// Get both refs for the enemy and the light it has step on it 
	LightObject = Cast<ALightObject>(LightRef);
	EnemyObject = Cast<AEnemyCharacter>(EnemyRef);

	DebuffPack debuffId = static_cast<DebuffPack>(FMath::RandRange(0, 3));

	UE_LOG(LogTemp, Warning, TEXT("DebuffId = %d "), debuffId);

	switch (debuffId)
	{
		case DebuffPack::SLOWED_FLICKER:
			EnemyDebuffImpl(EnemyDebuff::SLOWED);
			LightActionImpl(LightAction::FLICKER);
			break;

		case DebuffPack::STUN_EXPLOTE:
			EnemyDebuffImpl(EnemyDebuff::STUN);
			LightActionImpl(LightAction::EXPLOTE);
			break;

		case DebuffPack::DELAY_EXPLOTE:
			EnemyDebuffImpl(EnemyDebuff::STUN);
			LightActionImpl(LightAction::DELAY_EXPLOTE);
			break;

		case DebuffPack::DELAY_SLOWED:
			EnemyDebuffImpl(EnemyDebuff::SLOWED);
			LightActionImpl(LightAction::DELAY_SLOWED);
			break;

		default:
			UE_LOG(LogTemp, Warning, TEXT("Something went wrong on light: %s "), *LightObject->GetName());
			break;
	}
}

//---------------------------------------------------------------------------
void ALevelSystemIlumination::PlayerOnLight(UObject* LightRef)
{
	UE_LOG(LogTemp, Warning, TEXT("Player Enter"));
}

//---------------------------------------------------------------------------
void ALevelSystemIlumination::PlayerOffLight(UObject* LightRef)
{
	UE_LOG(LogTemp, Warning, TEXT("Player Get out"));
}

