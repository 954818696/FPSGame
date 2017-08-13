// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBBasePlayerController.h"
#include "GameLogic/GameRules/DBCheatManager.h"

ADBBasePlayerController::ADBBasePlayerController(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CheatClass = UDBCheatManager::StaticClass();
}


void ADBBasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();


}

void ADBBasePlayerController::RestartLevel()
{
	UEventSets::Clear();
	Super::RestartLevel();
}
