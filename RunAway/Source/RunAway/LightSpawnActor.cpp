

#include "LightSpawnActor.h"
#include "UObject/ConstructorHelpers.h"

ALightSpawnActor::ALightSpawnActor()
{
	// Load the data base Level
	static ConstructorHelpers::FObjectFinder<UDataTable> LevelLightsDataObject(TEXT("DataTable'/Game/BE/DataBases/LevelStremerData/LevelLights.LevelLights'"));
	if (LevelLightsDataObject.Succeeded())
	{
		LevelLightsDataTable = LevelLightsDataObject.Object;
	}

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Mesh"));
	SetRootComponent(CollisionMesh);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component"));
	Arrow->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ALightSpawnActor::BeginPlay()
{
	//Load the lights information needed for the level
	LoadLevelLightsInfo();

	if (SpawnLightMesh)
	{
		// Set the new rotation and location for the light
		FVector location = ALightSpawnActor::AActor::GetActorLocation();
		FRotator rotation = CollisionMesh->GetComponentRotation();

		// Spawn the actor with the correct location
		LightObjectRef = ALightSpawnActor::GetWorld()->SpawnActor<ALightObject>(ALightObject::StaticClass(), location , rotation, FActorSpawnParameters());

		if (LightObjectRef)
		{
			// Light Mesh Info
			auto staticLightMeshComponent = LightObjectRef->StaticLightMeshComp;
			staticLightMeshComponent->SetStaticMesh(SpawnLightMesh);
			staticLightMeshComponent->SetWorldScale3D(FVector(LightWorldScale));

			FLevelLightStruct* LevelLightObject = LevelLightsObjectMap.Find(LightTypeEnum);
			if (LevelLightObject)
			{
				// TODO: maybe we could add some properties into the csv, more work for later or find another way
				// Light properties Info (Rotation and location)
				auto LightProperties = LightObjectRef->LightComponent;
				LightProperties->SetRelativeLocation(FVector(LevelLightObject->LightPosition_X, LevelLightObject->LightPosition_Y, LevelLightObject->LightPosition_Z));
				LightProperties->SetRelativeRotation(FRotator(LevelLightObject->LightRotation_X, LevelLightObject->LightRotation_Y, LevelLightObject->LightRotation_Z));

				// Destroy the actor after the light has been spawned
				ALightSpawnActor::AActor::Destroy();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Could not initialize the light object actor on %s"), *ALightSpawnActor::AActor::GetName());
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Could not initialize the light object actor on %s"), *ALightSpawnActor::AActor::GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing Light mesh on %s "), *ALightSpawnActor::AActor::GetName());
	}

	Super::BeginPlay();
}

//---------------------------------------------------------------------------
// Load the lights information needed for the level
//---------------------------------------------------------------------------
void ALightSpawnActor::LoadLevelLightsInfo()
{
	// Load the lights data base values
	if (LevelLightsDataTable)
	{
		// Create context for the Find row parameter
		static const FString LevelLightsDataBasecontext(TEXT("LevelLightsDataTable Context"));

		// Get the list of indexis
		TArray<FName> LevelLightsRows = LevelLightsDataTable->GetRowNames();

		// light object ref
		FLevelLightStruct* lightObject;

		// iter trought the database
		for (int i = 0; i < LevelLightsRows.Num(); i++)
		{
			// Key of the row id
			FString RowKeyId = LevelLightsRows[i].ToString();

			// We found our row
			lightObject = LevelLightsDataTable->FindRow<FLevelLightStruct>(*RowKeyId, LevelLightsDataBasecontext, true);

			LevelLightsObjectMap.Add(static_cast<LevelLightType>(i), *lightObject);
		}
	}
}

