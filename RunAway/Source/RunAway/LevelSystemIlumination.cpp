// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSystemIlumination.h"
#include "LightObject.h"
#include "Kismet/GameplayStatics.h"
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
//	PUBLIC
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Called every frame
//---------------------------------------------------------------------------
void ALevelSystemIlumination::Tick(float DeltaTime)
{
	// Retrieves the total of lights in the level
	GetLightList();

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
void ALevelSystemIlumination::GetLightList()
{
	TArray<AActor*> ListOfLights;

	UGameplayStatics::GetAllActorsOfClass(ALevelSystemIlumination::GetWorld(), ALightObject::StaticClass(), ListOfLights);

	UE_LOG(LogTemp, Warning, TEXT("Number of lights in the level  %d"), ListOfLights.Num());
}
