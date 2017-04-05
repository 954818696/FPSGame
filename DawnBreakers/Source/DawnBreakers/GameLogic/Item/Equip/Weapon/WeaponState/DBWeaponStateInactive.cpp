// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponStateInactive.h"

UDBWeaponStateInactive::UDBWeaponStateInactive(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_StateID = EWeaponState::EWeaponState_Inactive;
}

void UDBWeaponStateInactive::EnterWeaponState()
{
	DAWNBREAKERS_LOG_INFO("EnterWeaponState:EWeaponState_Inactive %s", *GetWeapon()->GetName());
	m_bHandled = true;
}

void UDBWeaponStateInactive::ExitWeaponState()
{
	DAWNBREAKERS_LOG_INFO("ExitWeaponState:EWeaponState_Inactive %s", *GetWeapon()->GetName());
}

bool UDBWeaponStateInactive::CanTransferTo(EWeaponState::Type NewState, UDBWeaponStateBase* State)
{
	if (NewState == EWeaponState::EWeaponState_EquipingDirectly ||
		NewState == EWeaponState::EWeaponState_EquipingFromInventory)
	{
		return true;
	}

	return false;
}
