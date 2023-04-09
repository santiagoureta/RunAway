// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSystemIlumination.h"
#include "LightObject.h"
#include "PlayerCharacter.h"
#include "EnemyCharacter.h"
#include "LightSpawnActor.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"

//---------------------------------------------------------------------------
// CONSTRUCTOR
//---------------------------------------------------------------------------
ALevelSystemIlumination::ALevelSystemIlumination()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALevelSystemIlumination::BeginPlay()
{
	OwningWorld = GetWorld();

	Super::BeginPlay();
}

//---------------------------------------------------------------------------
// Called every frame
//---------------------------------------------------------------------------
void ALevelSystemIlumination::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//---------------------------------------------------------------------------
// PUBLIC
//---------------------------------------------------------------------------
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
		SetEnemyDebuff(EnemyDebuff::SLOWED);
		SetLightAction(LightAction::FLICKER);
		break;

	case DebuffPack::STUN_EXPLOTE:
		SetEnemyDebuff(EnemyDebuff::STUN);
		SetLightAction(LightAction::EXPLOTE);
		break;

	case DebuffPack::DELAY_EXPLOTE:
		SetEnemyDebuff(EnemyDebuff::STUN);
		SetLightAction(LightAction::DELAY_EXPLOTE);
		break;

	case DebuffPack::DELAY_SLOWED:
		SetEnemyDebuff(EnemyDebuff::SLOWED);
		SetLightAction(LightAction::DELAY_SLOWED);
		break;

	default:
		UE_LOG(LogTemp, Warning, TEXT("Something went wrong on light: %s "), *LightObject->GetName());
		break;
	}
}

//---------------------------------------------------------------------------
void ALevelSystemIlumination::PlayerOnLight(UObject* LightRef)
{
	LightObject = Cast<ALightObject>(LightRef);

	if (mLightWatched.Find(*LightObject->GetName())) return;

	mLightWatched.Add(*LightObject->GetName(), LightObject);
}

//---------------------------------------------------------------------------
void ALevelSystemIlumination::PlayerOffLight(UObject* LightRef)
{
	// TODO: Make something regarding the player off the light
}

//---------------------------------------------------------------------------
// PRIVATE
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void ALevelSystemIlumination::StartShutDown()
{
	// method that will start the light system to start shutting down
	int lightListSize = lightList.Num();

	if (lightListSize == 0) return;

	int AvailablePercentage = (30 * lightListSize) / 100;

	if (mLightWatched.Num() < AvailablePercentage) return;

	int LightToTurnOff = FMath::RandRange(0, lightListSize - 1);

	ALightObject* lightElem = lightList[LightToTurnOff];

	if (!lightElem->GetIsLightAvailable()) return;

	if (lightElem->GetIsLightFlickering()) return;

	// Logic made to each light that fullfill the requirements
	lightElem->FlickeringLight();

	UE_LOG(LogTemp, Warning, TEXT("Light Started Flickering by the system = %s "), *lightElem->GetName());
}

//---------------------------------------------------------------------------
void ALevelSystemIlumination::RenderLights()
{
	TSubclassOf<ALightSpawnActor> lightSpawnActor;
	lightSpawnActor = ALightSpawnActor::StaticClass();
	TArray<AActor*> outActors;

	// Get all the spawners for the lights on the world
	UGameplayStatics::GetAllActorsOfClass(OwningWorld, lightSpawnActor, outActors);

	ALevelSystemIlumination* levelSystemRef = this;

	for (auto& lightActorElem : outActors)
	{
		ALightSpawnActor* lightSpawnerObject = Cast<ALightSpawnActor>(lightActorElem);
		lightSpawnerObject->StartSpawningLights(levelSystemRef);
	}
}

//---------------------------------------------------------------------------
void ALevelSystemIlumination::SetLightList()
{
	TSubclassOf<ALightObject> lightActor;
	lightActor = ALightObject::StaticClass();
	TArray<AActor*> outActors;

	// Get all the spawners for the lights on the world
	UGameplayStatics::GetAllActorsOfClass(OwningWorld, lightActor, outActors);

	// Saved the lights object list
	for (auto& lightObjElem : outActors)
	{
		lightList.Add(Cast<ALightObject>(lightObjElem));
	}
}

//---------------------------------------------------------------------------
void ALevelSystemIlumination::SetLightAction(LightAction LightActionId)
{
	if (LightObject == NULL) return;

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
			UE_LOG(LogTemp, Warning, TEXT("Something went wrong applying the action for the light: %s "), *LightObject->GetName());
			break;
	}
}

//---------------------------------------------------------------------------
void ALevelSystemIlumination::SetEnemyDebuff(EnemyDebuff DebuffId)
{
	if (EnemyObject == NULL) return;
	
	// Check which debuff to apply
	switch (DebuffId)
	{
		case EnemyDebuff::SLOWED:
			EnemyObject->SlowEnemy();
			break;
			
		case EnemyDebuff::STUN:
			EnemyObject->StunEnemy();
			break;

		default:
			UE_LOG(LogTemp, Warning, TEXT("Something went wrong when applying the debuff on: %s "), *EnemyObject->GetName());
		break;
	}

}

