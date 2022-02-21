// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class RUNAWAY_API MainUtilities
{

public:

	enum GameStateEnum
	{
		GAME_INVALID = -1,
		GAME_STARTING = 0,
		GAME_READY = 1,
		GAME_RUNNING = 2,
		GAME_FINISHED = 3,
		GAME_FAILED = 4,

		GAME_NUMS = 6
	};

	enum GenerationStepsEnum
	{
		GENERATING_NOT_STARTED = -1,
		GENERATING_STARTING = 0,
		GENERATING_FAILED = 1,
		GENERATING_COMPLETED = 2,

		GENERATING_NUMS = 4
	};

	const FName GenerationStepsStrings[GenerationStepsEnum::GENERATING_NUMS] = {"NOT_STARTED","STARTING","FAILED","COMPLETED"};

	const FName GameStateStrings[GameStateEnum::GAME_NUMS] = { "INVALID","STARTING","READY","RUNNING","FINISHED"};

private:

};


