// Copyright 2021 - 25/12/2021 - Santiago Ureta - RunAway

#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Animation/AnimInstance.h"
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//---------------------------------------------------------------------------
// Player Constructor
//---------------------------------------------------------------------------
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(RootComponent);
	FollowCamera->bUsePawnControlRotation = true;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = PlayerMaxWalkSpeed;
	PlayerIsRunning = false;

}

//---------------------------------------------------------------------------
// BEGIN PLAY
//---------------------------------------------------------------------------
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

//---------------------------------------------------------------------------
// TICK
//---------------------------------------------------------------------------
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	IsPlayerRunning();
}

//---------------------------------------------------------------------------
// Called to bind functionality to input
//---------------------------------------------------------------------------
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Player Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerYawInput);

	// Player Actions
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APlayerCharacter::StartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &APlayerCharacter::StopRunning);
}

//---------------------------------------------------------------------------
//	PRIVATE
//---------------------------------------------------------------------------
// Update the config for the MoveForward state
//---------------------------------------------------------------------------
void APlayerCharacter::IsPlayerRunning()
{
	//TODO: Implement IsRunning Method
}

//---------------------------------------------------------------------------
// Manage the movement from the player (FORWARD - BACKWARDS)
//---------------------------------------------------------------------------
void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && Value != 0.f)
	{
		// Find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// Add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

//---------------------------------------------------------------------------
// Manage the movement from the player (RIGHT - LEFT)
//---------------------------------------------------------------------------
void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && Value != 0.f)
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

//---------------------------------------------------------------------------
// Manage the movement from the player (START RUNNING)
//---------------------------------------------------------------------------
void APlayerCharacter::StartRunning()
{
	PlayerIsRunning = true;
	GetCharacterMovement()->MaxWalkSpeed = PlayerMaxRunSpeed;
}

//---------------------------------------------------------------------------
// Manage the movement from the player (STOP RUNNING)
//---------------------------------------------------------------------------
void APlayerCharacter::StopRunning()
{
	PlayerIsRunning = false;
	GetCharacterMovement()->MaxWalkSpeed = PlayerMaxWalkSpeed;
}

