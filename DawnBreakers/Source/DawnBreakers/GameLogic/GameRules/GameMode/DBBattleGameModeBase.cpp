// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBBattleGameModeBase.h"
#include "GameLogic/Character/Player/Controller/DBPlayerController.h"

ADBBattleGameModeBase::ADBBattleGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerControllerClass = ADBPlayerController::StaticClass();

	//PlayerStateClass = 
	//GameStateClass = 
	//SpectatorClass = 
}

void ADBBattleGameModeBase::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ADBPlayerController * PC = Cast<ADBPlayerController>(NewPlayer);
	if (PC)
	{
		if (HasMatchEnded())
		{
			PC->EnterState(EPlayerInGameState::EndMatch);
		}
		else
		{
			PC->EnterState(EPlayerInGameState::PrepareForGettingIn);
		}
	}
}

void ADBBattleGameModeBase::RestartPlayer(AController* NewPlayer)
{
	return;
}


void ADBBattleGameModeBase::SpawnPlayer(ADBBasePlayerController * PC)
{

}

void ADBBattleGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void ADBBattleGameModeBase::InitGameState()
{
	Super::InitGameState();
}

void ADBBattleGameModeBase::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void ADBBattleGameModeBase::DefaultTimer()
{

}

void ADBBattleGameModeBase::StartMatch()
{
	Super::StartMatch();
}

void ADBBattleGameModeBase::SetPlayerDefaults(APawn* PlayerPawn)
{

}

void ADBBattleGameModeBase::FinishMatch()
{
	if (IsMatchInProgress())
	{
		EndMatch();

	}
}



