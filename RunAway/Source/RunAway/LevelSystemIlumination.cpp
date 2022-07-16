// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSystemIlumination.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

// Sets default values
ALevelSystemIlumination::ALevelSystemIlumination()
{
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
// Spawn the lights
//---------------------------------------------------------------------------
bool ALevelSystemIlumination::CreateLightSystem(TArray<AIluminationSystem*> &LightList)
{
	if (LightList.Num() > 0)
	{
		int changePositionVariable = 700;
		for (auto lightElem : LightList)
		{
			int levelChunkType = lightElem->GetLevelChunkType();
			int lightsPerChunk = lightElem->GetLevelLightsCount();
			FVector levelChunkPosition = lightElem->GetLevelChunkPosition();
			FVector levelChunkDirection = lightElem->GetLevelChunkDirection();
			
			if (levelChunkType == MainUtilities::LevelTypeEnum::LEVEL_TYPE_STREET)
			{
				for (size_t i = 0; i < lightsPerChunk; i++)
				{
					// Spawning the light
					Asystem = GetWorld()->SpawnActor<AIluminationSystem>();
					if (Asystem)
					{
						// create new position
						FVector position;
						int NewPosition_X;
						int NewPosition_Y;

						int currentPosition_X = levelChunkPosition.X;
						int currentPosition_Y = levelChunkPosition.Y;

						if (i == 0)
						{
							NewPosition_X = currentPosition_X + changePositionVariable;
							NewPosition_Y = currentPosition_Y + changePositionVariable;
						}
						else
						{
							NewPosition_X = currentPosition_X - changePositionVariable;
							NewPosition_Y = currentPosition_Y - changePositionVariable;
						}

						position.Set(NewPosition_X, NewPosition_Y, 0);

						// override the light position
						Asystem->OverrideLightPosition(position, levelChunkDirection);
					}
					else
					{
						// someting went wrong
						return false;
					}
				}
			}
		}
		return IluminationSystemReady();
	}
	else
	{
		return false;
	}
}

//---------------------------------------------------------------------------
//	PRIVATE
//---------------------------------------------------------------------------