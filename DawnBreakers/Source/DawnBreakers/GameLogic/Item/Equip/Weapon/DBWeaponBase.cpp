// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponBase.h"

ADBWeaponBase::ADBWeaponBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{


	m_WeaponStateMachine = ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateMachine>(this, TEXT("WeaponStateMachine"), false);
}

void ADBWeaponBase::OnEquip(ADBCharacter* ItemOwner, bool bEquipedWeaponFromInventory)
{

	SetItemOwner(ItemOwner);

	//  为了日后做捡起武器和身上现有武器切换的区分
	if (bEquipedWeaponFromInventory)
	{
		m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_EquipingFromInventory);
	}
	else 
	{
		m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_EquipingDirectly);
	}
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
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_Reloading);
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
	{
		return true;
	}

	return false;
}