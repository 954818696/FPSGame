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
	
	UDBWeaponStateBase* PrevState = m_WeaponStateMachine->GetPrevState();

	if (PrevState->GetStateID() == EWeaponState::EWeaponState_Attack)
	{
		GetWeapon()->PlayFireShotEffectByIndex(m_AfterFiringSmokeEffects);
	}
}

void UDBShootWeaponStateActive::ExitWeaponState()
{
	GetWeapon()->StopFireShotEffectByIndex(m_AfterFiringSmokeEffects);

	Super::ExitWeaponState();
}
