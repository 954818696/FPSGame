// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBZombieSurviveGameMode.h"

ADBZombieSurviveGameMode::ADBZombieSurviveGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerControllerClass = ADBZombieModePlayerController::StaticClass();
	NeedRespawn = false;
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
		//VictimPawn->DetachFromControllerPendingDestroy();
	}
}

void ADBZombieSurviveGameMode::DefaultTimer()
{

}

