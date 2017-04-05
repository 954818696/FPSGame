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
	ADBCharacter *TCharacter = GetWeaponOwner();
	if (TCharacter)
	{
		TCharacter->UpdateIronSightLoc(GetWeapon());
	}
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
		if (NewState == EWeaponState::EWeaponState_Attack)
		{
			if (State->IsA(UDBWeaponStateFiring::StaticClass()))
			{
				UDBWeaponStateFiring* FiringState = Cast<UDBWeaponStateFiring>(State);
				bool IsHaveAmmo = GetWeaponOwner()->GetInventory()->IsHaveAmmo(FiringState->m_CostAmmoType);
				if (!IsHaveAmmo)
				{
					GetWeapon()->PlayWeaponSound(FiringState->m_RunOutOfAmmoSound);
				}
				return IsHaveAmmo;
			}
		}
		return true;
	}
	return false;
}
