// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponStateEquipFromInventory.h"



UDBWeaponStateEquipFromInventory::UDBWeaponStateEquipFromInventory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_StateID = EWeaponState::EWeaponState_EquipingFromInventory;

}

void UDBWeaponStateEquipFromInventory::InitState()
{
	if (!EquipAnimFinishHandle.IsValid())
	{
		GetWeapon()->OnEquipAnimFinish().AddUObject(this, &UDBWeaponStateEquipFromInventory::OnEquipAnimFinish);
	}
}

void UDBWeaponStateEquipFromInventory::EnterWeaponState()
{
	DAWNBREAKERS_LOG_INFO("EnterWeaponState:EWeaponState_EquipingFromInventory");
	m_bHandled = false;

	ADBCharacter *TCharacter = GetWeaponOwner();
	if (TCharacter)
	{
		TCharacter->PlayAnimMontage(m_EquipAnim, 1.f, NAME_None);
	}
}

void UDBWeaponStateEquipFromInventory::ExitWeaponState()
{
	DAWNBREAKERS_LOG_INFO("ExitWeaponState:EWeaponState_EquipingFromInventory");
}

bool UDBWeaponStateEquipFromInventory::CanTransferTo(EWeaponState::Type NewState)
{
	if (IsHandled())
	{
		return true;
	}

	return false;
}

void UDBWeaponStateEquipFromInventory::OnEquipAnimFinish()
{
	m_bHandled = true;
	GetOuterUDBWeaponStateMachine()->GotoState(EWeaponState::EWeaponState_Active);
}

