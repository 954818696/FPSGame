// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameLogic/GameRules/GameMode/DBBattleGameModeBase.h"
#include "DBZombieSurviveGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API ADBZombieSurviveGameMode : public ADBBattleGameModeBase
{
	GENERATED_UCLASS_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = ADBZombieSurviveGameMode)
	class ADBZombieCharacter* SpawnZombie();
	
};
