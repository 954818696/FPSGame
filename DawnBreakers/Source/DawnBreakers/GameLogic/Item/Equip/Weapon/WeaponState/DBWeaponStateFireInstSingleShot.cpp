// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponStateFireInstSingleShot.h"

UDBWeaponStateFireInstSingleShot::UDBWeaponStateFireInstSingleShot(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void UDBWeaponStateFireInstSingleShot::EnterWeaponState()
{
	Fire();
	GetWeapon()->GetWorldTimerManager().SetTimer(TimerHandle_RefireTimer, this, &UDBWeaponStateFireInstSingleShot::RefireTimer, m_TimeBetweenShots, true);
}

void UDBWeaponStateFireInstSingleShot::RefireTimer()
{
	DAWNBREAKERS_LOG_INFO("UDBWeaponStateFireInstSingleShot::RefireTimer");
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_Active);
}
