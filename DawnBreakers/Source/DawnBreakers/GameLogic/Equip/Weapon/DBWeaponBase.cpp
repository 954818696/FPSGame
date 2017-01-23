// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponBase.h"

ADBWeaponBase::ADBWeaponBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_WeaponStateMachine = ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateMachine>(this, TEXT("WeaponStateMachine"), false);
}

void ADBWeaponBase::OnEquip()
{
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_Equiping);
}

void ADBWeaponBase::OnUnEquip()
{
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_Unequiping);
}

void ADBWeaponBase::OnSwitchMode()
{
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_SwitchMode);
}

void ADBWeaponBase::OnReload()
{
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_Equiping);
}

void ADBWeaponBase::OnStartFire()
{
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_Firing);
}

void ADBWeaponBase::OnStopFire()
{
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_Active);
}

bool ADBWeaponBase::IsInState(EWeaponState::Type WeaponState) const
{
	if (m_WeaponStateMachine->IsInState(WeaponState))
		return true;

	return false;
}