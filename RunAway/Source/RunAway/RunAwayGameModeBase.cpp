// Fill out your copyright notice in the Description page of Project Settings.


#include "RunAwayGameModeBase.h"
#include "PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARunAwayGameModeBase::ARunAwayGameModeBase()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("'/Game/BE/Blueprints/Character/PlayerCharacter_BP'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}