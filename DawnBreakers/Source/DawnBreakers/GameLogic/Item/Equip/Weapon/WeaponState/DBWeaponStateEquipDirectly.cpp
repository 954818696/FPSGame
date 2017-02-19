// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponStateEquipDirectly.h"


UDBWeaponStateEquipDirectly::UDBWeaponStateEquipDirectly(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_StateID = EWeaponState::EWeaponState_EquipingDirectly;
}

void UDBWeaponStateEquipDirectly::EnterWeaponState()
{
	DAWNBREAKERS_LOG_INFO("EnterWeaponState:EWeaponState_EquipingDirectly");

}

void UDBWeaponStateEquipDirectly::ExitWeaponState()
{
	DAWNBREAKERS_LOG_INFO("ExitWeaponState:EWeaponState_EquipingDirectly");
}

bool UDBWeaponStateEquipDirectly::IsHandled()
{
	return true;
}

