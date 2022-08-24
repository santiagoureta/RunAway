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

	enum LogEnum
	{
		LOG_GAME_STATE,
		LOG_GENERATION_STATE,
		LOG_NUMS
	};

	enum GenerationTypeEnum
	{
		DATABASE_TYPE,
		WORLD_TYPE,
		ILUMINATION_TYPE,
		PLAYER_TYPE,
		ENEMY_TYPE,
		GAME_TYPE,
		NUMS_TYPE
	};

	enum LevelTypeEnum
	{
		LEVEL_TYPE_INVALID = -1,
		LEVEL_TYPE_HOUSE = 0,
		LEVEL_TYPE_STREET = 1,
		LEVEL_TYPE_STREET_CORNER = 2,
		LEVEL_TYPE_GRASS = 3,
		LEVEL_TYPE_PARK = 4,
		LEVEL_TYPE_GAS_STATION = 5,
		LEVEL_TYPE_APARTMENT = 6,
		LEVEL_TYPE_FOOD_PLACES = 7,
		LEVEL_TYPE_PASSAGE = 8,

		LEVEL_TYPE_NUM = LEVEL_TYPE_PASSAGE
	};

	enum LevelLightTypeEnum
	{
		LEVEL_LIGHT_TYPE_STREET,
		LEVEL_LIGHT_TYPE_STREET_CORNER,
		LEVEL_LIGHT_TYPE_PASSAGE
	};

	const FName GenerationStepsStrings[GenerationStepsEnum::GENERATING_NUMS] = {"NOT_STARTED","STARTING","FAILED","COMPLETED"};

	const FName GameStateStrings[GameStateEnum::GAME_NUMS] = { "INVALID","STARTING","READY","RUNNING","FINISHED"};

private:

};


