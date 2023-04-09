// Fill out your copyright notice in the Description page of Project Settings.


#include "LightObject.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/SphereComponent.h"
#include "LevelSystemIlumination.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

//---------------------------------------------------------------------------
//	CONSTRUCTOR
//---------------------------------------------------------------------------
ALightObject::ALightObject()
{
	PrimaryActorTick.bCanEverTick = true;

	// Pre setup general information for the light mesh component
	StaticLightMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	StaticLightMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetRootComponent(StaticLightMeshComp);

	// sphere collision that will retrieve the number of lights inside the radius we defined on the bp
	NearbyDetection = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	NearbyDetection->SetGenerateOverlapEvents(true);
	NearbyDetection->SetSphereRadius(310);
	NearbyDetection->SetupAttachment(RootComponent);

	// Pre setup general information for the spot light
	LightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("LightRepresentation"));
	LightComponent->AttachToComponent(StaticLightMeshComp, FAttachmentTransformRules::KeepRelativeTransform);

	LightComponent->Intensity = 30000;
	FLinearColor color = FVector4(0.9215687, 0.6862745, 0.2039216, 1);
	LightComponent->SetLightColor(color);
	LightComponent->AttenuationRadius = 1500;
	LightComponent->InnerConeAngle = 30;
	LightComponent->OuterConeAngle = 55;
	LightComponent->SourceRadius = 40;
	LightComponent->SoftSourceRadius = 300;
	LightComponent->bUseTemperature = true;
	LightComponent->Temperature = 55000;
}

// Called when the game starts or when spawned
void ALightObject::BeginPlay()
{
	Super::BeginPlay();
}

