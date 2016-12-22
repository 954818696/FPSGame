// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "DGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API ADGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ADGameMode();
	
	virtual void InitGameState() override;

	virtual void PreInitializeComponents() override;
	
protected:
	FTimerHandle WorldDayTimerHandle;
	void WorldDayTimer();

public:
	UPROPERTY(EditDefaultsOnly, Category = "Time")
	int32 miBeginTimeForDayInMinutes;
};
