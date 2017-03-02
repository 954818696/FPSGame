// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponStateUnEquiping.h"

UDBWeaponStateUnEquiping::UDBWeaponStateUnEquiping(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_StateID = EWeaponState::EWeaponState_Unequiping;

}


void UDBWeaponStateUnEquiping::InitState()
{
	if (!UnEquipAnimFinishHandle.IsValid())
	{
		GetWeapon()->OnUnEquipAnimFinish().AddUObject(this, &UDBWeaponStateUnEquiping::OnUnEquipAnimFinish);
	}
}

void UDBWeaponStateUnEquiping::EnterWeaponState()
{
	DAWNBREAKERS_LOG_INFO("EnterWeaponState:EWeaponState_Unequiping");
	m_bHandled = false;

	ADBCharacter *TCharacter = GetWeaponOwner();
	if (TCharacter)
	{
		TCharacter->PlayAnimMontage(m_UnEquipAnim, 1.f, NAME_None);
	}
}

void UDBWeaponStateUnEquiping::ExitWeaponState()
{
	DAWNBREAKERS_LOG_INFO("ExitWeaponState:EWeaponState_Unequiping");
}

bool UDBWeaponStateUnEquiping::CanTransferTo(EWeaponState::Type NewState)
{
	if (NewState == EWeaponState::EWeaponState_Active && IsHandled())
	{
		return true;
	}

	return true;
}

void UDBWeaponStateUnEquiping::OnUnEquipAnimFinish()
{
	m_bHandled = true;
	GetOuterUDBWeaponStateMachine()->GotoState(EWeaponState::EWeaponState_Inactive);
}
