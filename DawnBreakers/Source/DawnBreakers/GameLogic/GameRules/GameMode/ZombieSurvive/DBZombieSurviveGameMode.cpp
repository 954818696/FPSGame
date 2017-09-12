// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBZombieSurviveGameMode.h"
#include "ZombieSurvivalGameState.h"
#include "ZombieSurvivalPlayerState.h"
#include "ZombieSurvivalHUD.h"

ADBZombieSurviveGameMode::ADBZombieSurviveGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerControllerClass = ADBZombieModePlayerController::StaticClass();
	GameStateClass = AZombieSurvivalGameState::StaticClass();
	PlayerStateClass = AZombieSurvivalPlayerState::StaticClass();
	HUDClass = AZombieSurvivalHUD::StaticClass();

	NeedRespawn = false;
}

void ADBZombieSurviveGameMode::PreInitializeComponents()
{
	AGameMode::PreInitializeComponents();

	GetWorldTimerManager().SetTimer(TimerHandle_WorldDayTimer, this, &ADBZombieSurviveGameMode::WorldDayTimer, GetWorldSettings()->GetEffectiveTimeDilation(), true);
}

void ADBZombieSurviveGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (NeedRespawn)
	{
		static float CurTime = 0.f;
		CurTime += DeltaSeconds;
		if (CurTime > RespawnTime)
		{
			NeedRespawn = false;
			CurTime = 0.f;
	
			for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
			{
				ADBPlayerController* PlayerController = Cast<ADBPlayerController>(*It);
				if (PlayerController)
				{
					SpawnPlayer(PlayerController);
				}
			}

		}
	}
}

class ADBZombieCharacter* ADBZombieSurviveGameMode::SpawnZombie()
{
	return nullptr;
}

void ADBZombieSurviveGameMode::SpawnPlayer(ADBBasePlayerController * PC)
{
	UEventSets::Instance()->OnRestartPlayer.Broadcast();

	Super::SpawnPlayer(PC);
}

void ADBZombieSurviveGameMode::Killed(AController* Killer, AController* VictimPlayer, APawn* VictimPawn, const UDamageType* DamageType)
{
	if (VictimPlayer->IsA(ADBPlayerController::StaticClass()))
	{
		UEventSets::Instance()->OnRestartPlayer.Broadcast();
		NeedRespawn = true;
	}
}

void ADBZombieSurviveGameMode::FinishMatch()
{
	//DAWNBREAKERS_LOG_ERROR("***************ADBZombieSurviveGameMode::FinishMatch");
	GetWorldTimerManager().ClearTimer(TimerHandle_WorldDayTimer);

	Super::FinishMatch();
}

void ADBZombieSurviveGameMode::WorldDayTimer()
{
	AZombieSurvivalGameState* TGameState = Cast<AZombieSurvivalGameState>(GameState);
	if (TGameState)
	{
		TGameState->m_iElapsedGameMinutes += TGameState->GetTimeOfDayIncrement();
		TGameState->GetAndUpdateNightState();
	}
}

