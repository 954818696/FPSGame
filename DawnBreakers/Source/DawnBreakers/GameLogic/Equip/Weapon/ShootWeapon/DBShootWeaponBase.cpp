// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBShootWeaponBase.h"
#include "GameLogic/Equip/Weapon/ShootWeapon/WeaponState/DBWeaponStateMachine.h"



ADBShootWeaponBase::ADBShootWeaponBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_WeaponStateMachine = ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateMachine>(this, TEXT("WeaponStateMachine"), false);

}

void ADBShootWeaponBase::OnStartFire()
{

}

void ADBShootWeaponBase::OnStopFire()
{

}
