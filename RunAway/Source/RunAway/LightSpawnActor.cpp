

#include "LightSpawnActor.h"
#include "UObject/ConstructorHelpers.h"

//---------------------------------------------------------------------------
// CONSTRUCTOR
//---------------------------------------------------------------------------
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

	//Load the lights information needed for the level
	LoadLevelLightsInfo();
}

void ALightSpawnActor::BeginPlay()
{
	Super::BeginPlay();
}

//---------------------------------------------------------------------------
// PRIVATE
//---------------------------------------------------------------------------

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

