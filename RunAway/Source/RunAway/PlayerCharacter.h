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

	class USphereComponent* GetNearbyLightDetectionComponent() { return NearbyLightsDetection; };

	UFUNCTION()
		void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:

	//! Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	//! Camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "APlayerCharacter::CameraComponent", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	//! Sphere component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "APlayerCharacter::CollisionComponent", meta = (AllowPrivateAccess = "true"))
		class USphereComponent* NearbyLightsDetection;

	//! Flag to know if the player is running
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "APlayerCharacter::PlayerState", meta = (AllowPrivateAccess = "true"))	
		bool PlayerIsRunning;

	//! Player Max walk speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "APlayerCharacter::DebugPlayerProperties", meta = (AllowPrivateAccess = "true"))
		float PlayerMaxWalkSpeed = 250.f;

	//! Player Max run speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "APlayerCharacter::DebugPlayerProperties", meta = (AllowPrivateAccess = "true"))
		float PlayerMaxRunSpeed = 850.f;

	//! Player Max Stamina
	int PlayerMaxStamina = 800;

	//! Player Min Stamina
	const int PlayerMinStamina = -150;

	//! Player Min Stamina
	int PlayerDelayStamina = 0;

	//! Player Current Stamina
	int CurrentPlayerStamina = 0;

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

};
