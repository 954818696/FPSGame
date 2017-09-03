// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBCheatManager.h"
#include "GameLogic/Character/Player/Controller/DBBasePlayerController.h"




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

void UDBCheatManager::KillSelf()
{
	ADBBasePlayerController* MyPC = GetOuterADBBasePlayerController();

	if (MyPC)
	{
		ADBCharacter* Player = Cast<ADBCharacter>(MyPC->GetPawn());
		if (Player)
		{
			float ActualHitDamage = 100000.f;

			FPointDamageEvent PointDmg;
			PointDmg.Damage = ActualHitDamage;

			Player->TakeDamage(PointDmg.Damage, PointDmg, MyPC, nullptr);
		}
	}
}
