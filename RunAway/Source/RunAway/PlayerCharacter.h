// Copyright 2021 - 25/12/2021 - Santiago Ureta - RunAway
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class RUNAWAY_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	//! Constructor of the player character class
	APlayerCharacter();

	//! Called every frame
	virtual void Tick(float DeltaTime) override;

	//! Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//! Function that allows the user to open the minimap
	UFUNCTION(BlueprintImplementableEvent, Category = "PlayerAction")
		void MobileGpsOpen();

protected:

	//! Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	//! Function to modify the player stamina
	virtual void IsPlayerRunning();

	//! Function that creates the forward-backwards movement for the player
	virtual void MoveForward(float Value);

	//! Function that creates the right-left movement for the player
	virtual void MoveRight(float Value);

	//! Function that Start the running action
	virtual void StartRunning();

	//! Function that Stop the running action
	virtual void StopRunning();

	//! Camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "APlayerCharacter::CameraComponent", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	//! SpringArm that controls the Scene Capture
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "APlayerCharacter::SceneCapture", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArmRenderMap;

	//! Scene Capture Comp
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "APlayerCharacter::SceneCapture", meta = (AllowPrivateAccess = "true"))
		class USceneCaptureComponent2D* SceneCapture;

	//! Sprite component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "APlayerCharacter::SceneCapture", meta = (AllowPrivateAccess = "true"))
		class UPaperSpriteComponent* SpriteComponent;

	//! SplineComponent
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "APlayerCharacter::SplineComponent", meta = (AllowPrivateAccess = "true"))
		class USplineComponent* SplineComponent;

	//! Flag to know if the player is running
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "APlayerCharacter::PlayerState", meta = (AllowPrivateAccess = "true"))
		bool PlayerIsRunning;

	//! Player Max walk speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "APlayerCharacter::DebugPlayerProperties", meta = (AllowPrivateAccess = "true"))
		float PlayerMaxWalkSpeed = 250.f;

	//! Player Max run speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "APlayerCharacter::DebugPlayerProperties", meta = (AllowPrivateAccess = "true"))
		float PlayerMaxRunSpeed = 850.f;

	//! Player Current Stamina
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "APlayerCharacter::DebugPlayerProperties", meta = (AllowPrivateAccess = "true"))
		float CurrentPlayerStamina = 0.0f;

	//! Player Max Stamina
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "APlayerCharacter::DebugPlayerProperties", meta = (AllowPrivateAccess = "true"))
		float PlayerMaxStamina = 1000.0f;

	//! Player Min Stamina
	const float PlayerMinStamina = -150.0f;

	//! Player Min Stamina
	float PlayerDelayStamina = 0.0f;

};
