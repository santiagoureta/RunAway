// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Particles/ParticleSystemComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

//---------------------------------------------------------------------------
// CONSTRUCTOR
//---------------------------------------------------------------------------
AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	smoke_1 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke_1"));
	smoke_1->SetRelativeLocation(FVector(0,0,-60));
	smoke_1->AttachTo(RootComponent);
	
	pawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("pawnSensing"));
	pawnSensing->bHearNoises = false;
	pawnSensing->SetPeripheralVisionAngle(55.0);
	pawnSensing->LOSHearingThreshold = 0.0;
	pawnSensing->HearingThreshold = 0.0;

	// Configure character movement
	GetCharacterMovement()->MaxWalkSpeed = EnemyNormalSpeed;
}

//---------------------------------------------------------------------------
// BEGIN PLAY
//---------------------------------------------------------------------------
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

//---------------------------------------------------------------------------
// TICK
//---------------------------------------------------------------------------
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//---------------------------------------------------------------------------
//	PUBLIC
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

