// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponStateDrop.h"


UDBWeaponStateDrop::UDBWeaponStateDrop(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_StateID = EWeaponState::EWeaponState_Drop;

}

void UDBWeaponStateDrop::EnterWeaponState()
{
	DAWNBREAKERS_LOG_INFO("EnterWeaponState:EWeaponState_Drop %s", *GetWeapon()->GetName());

	ADBCharacter* OwnerCharacter = GetWeaponOwner();
	ADBWeaponBase* Weapon = GetWeapon();
	if (OwnerCharacter && Weapon)
	{
		OwnerCharacter->GetInventory()->RemoveFromInventory(Weapon, true);
		m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_Inactive);
		UDBCharacterAnimInstance* TAnimInstance = OwnerCharacter->GetAnimInstance();
		if (TAnimInstance)
		{
			TAnimInstance->SetWeaponHoldStance(0);
		}
	}
}

void UDBWeaponStateDrop::ExitWeaponState()
{
	DAWNBREAKERS_LOG_INFO("ExitWeaponState:EWeaponState_Drop %s", *GetWeapon()->GetName());
}

bool UDBWeaponStateDrop::CanTransferTo(EWeaponState::Type NewState, UDBWeaponStateBase* State)
{
	if (NewState == EWeaponState::EWeaponState_Inactive && IsHandled())
	{
		return true;
	}

	return false;
}
