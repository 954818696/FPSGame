// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponStateActive.h"
#include "DBWeaponStateFiring.h"


UDBWeaponStateActive::UDBWeaponStateActive(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_StateID = EWeaponState::EWeaponState_Active;
}


void UDBWeaponStateActive::EnterWeaponState()
{
	DAWNBREAKERS_LOG_INFO("EnterWeaponState:EWeaponState_Active %s", *GetWeapon()->GetName());

}

void UDBWeaponStateActive::ExitWeaponState()
{
	DAWNBREAKERS_LOG_INFO("ExitWeaponState:EWeaponState_Active %s", *GetWeapon()->GetName());
}

bool UDBWeaponStateActive::CanTransferTo(EWeaponState::Type NewState, UDBWeaponStateBase* State)
{
	if (NewState != EWeaponState::EWeaponState_EquipingDirectly ||
		NewState != EWeaponState::EWeaponState_EquipingFromInventory)
	{
		return true;
	}
	return false;
}
