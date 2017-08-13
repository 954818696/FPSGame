// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBGameMode.h"
#include "GameLogic/Character/Player/Controller/DBBasePlayerController.h"
#include "GameLogic/Character/Player/DBCharacter.h"


ADBGameMode::ADBGameMode(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerControllerClass = ADBPlayerController::StaticClass();
	DefaultPawnClass = ADBCharacter::StaticClass();
}


