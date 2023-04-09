// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class RUNAWAY_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//! Function that stuns the enemy
	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy")
		void StunEnemy();

	//! Function that Teleport the enemy to a differtent location
	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy")
		void TeleportEnemy();

	//! Function that slows the enemy
	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy")
		void SlowEnemy();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AEnemyCharacter::EnemyInfo", meta = (AllowPrivateAccess = "true"))
		bool IsPlayerInRange = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AEnemyCharacter::EnemyInfo", meta = (AllowPrivateAccess = "true"))
		bool IsEnemyStunned = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AEnemyCharacter::EnemyInfo", meta = (AllowPrivateAccess = "true"))
		bool IsEnemyChasing = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AEnemyCharacter::EnemyInfo", meta = (AllowPrivateAccess = "true"))
		float EnemySpeedSlowed = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AEnemyCharacter::EnemyInfo", meta = (AllowPrivateAccess = "true"))
		float EnemyNormalSpeed = 1000.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AEnemyCharacter::Effects", meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* smoke_1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AEnemyCharacter::SensingComponent", meta = (AllowPrivateAccess = "true"))
		class UPawnSensingComponent* pawnSensing;
};
