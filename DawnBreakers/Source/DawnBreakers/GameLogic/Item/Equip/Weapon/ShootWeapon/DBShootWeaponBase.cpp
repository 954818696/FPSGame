// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBShootWeaponBase.h"


ADBShootWeaponBase::ADBShootWeaponBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void ADBShootWeaponBase::OnReload()
{
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_Reloading);
}

void ADBShootWeaponBase::OnSwitchMode()
{
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_SwitchMode);
}

void ADBShootWeaponBase::OnStopFire()
{
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_Active);
}

