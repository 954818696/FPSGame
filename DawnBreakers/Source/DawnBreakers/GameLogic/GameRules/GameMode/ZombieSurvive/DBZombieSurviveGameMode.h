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
	virtual void PreInitializeComponents() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = ADBZombieSurviveGameMode)
	class ADBZombieCharacter* SpawnZombie();

	virtual void SpawnPlayer(ADBBasePlayerController * PC) override;

	virtual void Killed(AController* Killer, AController* VictimPlayer, APawn* VictimPawn, const UDamageType* DamageType);

	UFUNCTION(BlueprintCallable, Category = ADBZombieSurviveGameMode)
	virtual void FinishMatch() override;

private:
	void WorldDayTimer();

private:
	const float RespawnTime= 6.f;

	bool NeedRespawn;
	
	FTimerHandle TimerHandle_WorldDayTimer;
};
