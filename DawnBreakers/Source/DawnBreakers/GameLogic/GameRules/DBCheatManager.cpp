// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBCheatManager.h"
#include "GameLogic/Character/DBBasePlayerController.h"




void UDBCheatManager::Test()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "UDBCheatManager!");
	ADBBasePlayerController* MyPC = GetOuterADBBasePlayerController();

	if (MyPC)
	{

	}
	
}

void UDBCheatManager::SetIronSight()
{

}
