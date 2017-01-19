// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponBase.h"
#include "GameLogic/Equip/Weapon/WeaponState/DBWeaponStateMachine.h"



ADBWeaponBase::ADBWeaponBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_WeaponStateMachine = ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateMachine>(this, TEXT("WeaponStateMachine"), false);

}

void ADBWeaponBase::OnStartFire()
{

}

void ADBWeaponBase::OnStopFire()
{

}