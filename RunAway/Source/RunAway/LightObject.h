// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightObject.generated.h"

UCLASS()
class RUNAWAY_API ALightObject : public AActor
{
	GENERATED_BODY()
	
public:	

	//! Contructors
	ALightObject();

	//! static mesh component ref
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LightInfo, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticLightMeshComp;

	//! spotlight component ref
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LightInfo, meta = (AllowPrivateAccess = "true"))
	class USpotLightComponent* LightComponent;

	UFUNCTION(BlueprintImplementableEvent, Category = "LightAction")
		void FlickeringLight();

	UFUNCTION(BlueprintImplementableEvent, Category = "LightAction")
		void LightToExplote();

	UFUNCTION(BlueprintImplementableEvent, Category = "LightAction")
		void LightToExploteWithDelay();

protected:

	virtual void BeginPlay() override;

private:

	//! Sphere component ref
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALightObject::CollisionComponent", meta = (AllowPrivateAccess = "true"))
		class USphereComponent* NearbyDetection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LightInfo, meta = (AllowPrivateAccess = "true"))
		bool IsLightAvailable = true;
};
