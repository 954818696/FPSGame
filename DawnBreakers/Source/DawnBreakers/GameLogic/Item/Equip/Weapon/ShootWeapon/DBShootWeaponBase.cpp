// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBShootWeaponBase.h"


ADBShootWeaponBase::ADBShootWeaponBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_AimCameraComp = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("AimCamera"));
	m_AimCameraComp->bUsePawnControlRotation = true;
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

