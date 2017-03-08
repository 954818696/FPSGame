// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponStateActive.h"


UDBWeaponStateActive::UDBWeaponStateActive(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_StateID = EWeaponState::EWeaponState_Active;
}


void UDBWeaponStateActive::EnterWeaponState()
{
	DAWNBREAKERS_LOG_INFO("EnterWeaponState:EWeaponState_Active %s", *GetWeapon()->GetName());
	// Animation for weapon active.
	//ADBCharacter *TCharacter = GetWeaponOwner();
	//if (TCharacter)
	//{
		//UDBCharacterAnimInstance* TAnimInstance = TCharacter->GetAnimInstance();
		//ADBWeaponBase* TWeapon = GetWeapon();
		//if (TAnimInstance && TWeapon)
		//{
		//	TAnimInstance->SetWeaponHoldStance(TWeapon->GetWeaponHoldStanceType());
		//}
	//}
}

void UDBWeaponStateActive::ExitWeaponState()
{
	DAWNBREAKERS_LOG_INFO("ExitWeaponState:EWeaponState_Active %s", *GetWeapon()->GetName());
}

bool UDBWeaponStateActive::CanTransferTo(EWeaponState::Type NewState)
{
	if (NewState != EWeaponState::EWeaponState_EquipingDirectly ||
		NewState != EWeaponState::EWeaponState_EquipingFromInventory)
	{
		return true;
	}

	return false;
}
