// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class RUNAWAY_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	// Constructor of the player character class
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "APlayerCharacter::Camera", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "APlayerCharacter::Mesh", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* MeshComponent;

	// Function that creates the forward-backwards movement for the player
	virtual void MoveForward(float Value);

	// Function that creates the right-left movement for the player
	virtual void MoveRight(float Value);

};
