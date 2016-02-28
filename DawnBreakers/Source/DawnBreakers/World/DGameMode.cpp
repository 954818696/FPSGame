// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DGameMode.h"
#include "DGameState.h"

ADGameMode::ADGameMode()
	: Super()
{
	GameStateClass = ADGameState::StaticClass();
	

	miBeginTimeForDayInMinutes = 8 * 60 ;
}

void ADGameMode::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	GetWorldTimerManager().SetTimer(WorldDayTimerHandle, this, &ADGameMode::WorldDayTimer, GetWorldSettings()->GetEffectiveTimeDilation(), true);
}

void ADGameMode::InitGameState()
{
	Super::InitGameState();

	ADGameState* MyGameState = Cast<ADGameState>(GameState);
	if (MyGameState)
	{
		MyGameState->miElapsedGameMinutes = miBeginTimeForDayInMinutes;
	}
}

void ADGameMode::WorldDayTimer()
{
	ADGameState* MyGameState = Cast<ADGameState>(GameState);
	if (MyGameState)
	{
		MyGameState->miElapsedGameMinutes += MyGameState->GetTimeOfDayIncrement();
		MyGameState->GetAndUpdateNightState();
	}
}