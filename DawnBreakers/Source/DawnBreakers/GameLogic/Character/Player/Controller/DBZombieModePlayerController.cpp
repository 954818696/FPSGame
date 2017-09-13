// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBZombieModePlayerController.h"
#include "GameLogic/GameRules/GameMode/ZombieSurvive/ZombieSurvivalHUD.h"

ADBZombieModePlayerController::ADBZombieModePlayerController(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void ADBZombieModePlayerController::SendHUDMsg_Implementation(const FString& Msg)
{
	AZombieSurvivalHUD* THUD = Cast<AZombieSurvivalHUD>(GetHUD());
	if (THUD)
	{
		THUD->HandleMsg(Msg);
	}
}

