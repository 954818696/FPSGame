// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBShootWeaponStateActive.h"




UDBShootWeaponStateActive::UDBShootWeaponStateActive()
	:m_AfterFiringSmokeEffects(-1)
{

}

void UDBShootWeaponStateActive::EnterWeaponState()
{
	Super::EnterWeaponState();
	
	GetWeapon()->PlayFireShotEffectByIndex(m_AfterFiringSmokeEffects);

	ADBCharacter *TCharacter = GetWeaponOwner();
	if (TCharacter)
	{
		TCharacter->UpdateIronSightLoc(GetWeapon());
	}
}

void UDBShootWeaponStateActive::ExitWeaponState()
{
	GetWeapon()->StopFireShotEffectByIndex(m_AfterFiringSmokeEffects);

	Super::ExitWeaponState();
}
