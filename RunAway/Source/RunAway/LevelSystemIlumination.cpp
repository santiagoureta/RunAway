// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSystemIlumination.h"
#include "LightObject.h"
#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

ALevelSystemIlumination::ALevelSystemIlumination()
{
	PrimaryActorTick.bCanEverTick = true;

	if (!OverlapActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Something went wrong the player character actor was not found"));
	}
}

// Called when the game starts or when spawned
void ALevelSystemIlumination::BeginPlay()
{
	PlayerCharacter = static_cast<APlayerCharacter*>(OverlapActor->GetDefaultObject());

	Super::BeginPlay();
}

//---------------------------------------------------------------------------
// Called every frame
//---------------------------------------------------------------------------
void ALevelSystemIlumination::Tick(float DeltaTime)
{	
	if (PlayerCharacter)
	{
		GetNearLights();
	}

	Super::Tick(DeltaTime);
}

//---------------------------------------------------------------------------
// Function that retrieves if the system is ready to continue
//---------------------------------------------------------------------------
bool ALevelSystemIlumination::IluminationSystemReady()
{
	isSystemReady = true;

	return isSystemReady;
}

//---------------------------------------------------------------------------
//	PRIVATE
//---------------------------------------------------------------------------
void ALevelSystemIlumination::GetNearLights()
{
	// TODO CONTINUE WITH THE LIGHT SYSTEM, we are close

	auto lightsInRange =  PlayerCharacter->GetNearbyLightDetectionComponent();

	for (auto& actorElem : lightsInRange->GetOverlapInfos())
	{
		UE_LOG(LogTemp, Warning, TEXT(" name %s"), *actorElem.OverlapInfo.Actor.Get()->GetFullName());
	}

}
