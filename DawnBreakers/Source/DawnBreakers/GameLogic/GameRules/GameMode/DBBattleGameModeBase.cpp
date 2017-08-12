// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBBattleGameModeBase.h"

ADBBattleGameModeBase::ADBBattleGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerControllerClass = ADBPlayerController::StaticClass();
	DefaultPawnClass = ADBCharacter::StaticClass();
	//PlayerStateClass = 
	//GameStateClass = 
	//SpectatorClass = 
}


