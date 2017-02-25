// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponStateEquipFromInventory.h"



UDBWeaponStateEquipFromInventory::UDBWeaponStateEquipFromInventory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_StateID = EWeaponState::EWeaponState_EquipingFromInventory;
}

void UDBWeaponStateEquipFromInventory::EnterWeaponState()
{

}

void UDBWeaponStateEquipFromInventory::ExitWeaponState()
{

}

