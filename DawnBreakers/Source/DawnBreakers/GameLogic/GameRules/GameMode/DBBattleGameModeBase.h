// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "DBBattleGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API ADBBattleGameModeBase : public AGameMode
{
	GENERATED_UCLASS_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = DBBattleGameMode)
	virtual void FinishMatch();

protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void InitGameState() override;

	virtual void PreInitializeComponents() override;
	
	virtual void DefaultTimer();

	virtual void StartMatch();

	virtual void SetPlayerDefaults(APawn* PlayerPawn) override;

protected:
	FTimerHandle TimerHandle_DefaultTimer;
};
