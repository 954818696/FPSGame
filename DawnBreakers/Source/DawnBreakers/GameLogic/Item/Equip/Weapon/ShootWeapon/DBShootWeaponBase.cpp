// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBShootWeaponBase.h"
#include "GameLogic/Item/Equip/Weapon/WeaponState/DBWeaponStateFiring.h"


ADBShootWeaponBase::ADBShootWeaponBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void ADBShootWeaponBase::OnReload()
{
	if (m_CurAmmosInClip < m_AmmoClipSize)
	{
		m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_Reloading);
	}
}

void ADBShootWeaponBase::OnSwitchMode()
{
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_SwitchMode);
}

void ADBShootWeaponBase::OnStartFire()
{
	ADBCharacter* TOwner = GetItemOwner();
	UDBWeaponStateFiring* TFiringState = Cast<UDBWeaponStateFiring>(m_WeaponStateMachine->GetState(EWeaponState::EWeaponState_Attack));
	if (TOwner && TFiringState)
	{
		bool IsHaveAmmo = TOwner->GetInventory()->IsHaveAmmo(TFiringState->m_CostAmmoType);
		if (IsHaveAmmo)
		{
			if (m_CurAmmosInClip == 0)
			{
				OnReload();
			}
			else
			{
				Super::OnStartFire();
			}
		}
		else
		{
			PlayOutOfAmmoSound();
		}
	}
}

void ADBShootWeaponBase::OnStopFire()
{
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_Active);
}

void ADBShootWeaponBase::SetCurAmmosInClip(int32 AmmoAmount)
{
	m_CurAmmosInClip = AmmoAmount < m_AmmoClipSize ? AmmoAmount : m_AmmoClipSize;
}

void ADBShootWeaponBase::ConsumeAmmo(EAmmoType AmmoType, int32 CostAmount)
{
	if (m_CurAmmosInClip > 0)
	{
		--m_CurAmmosInClip;
	}
	else
	{
		bool IsHaveAmmo = GetItemOwner()->GetInventory()->IsHaveAmmo(AmmoType);
		if (IsHaveAmmo)
		{
			OnReload();
		}
		else
		{
			OnStopFire();
			PlayOutOfAmmoSound();
		}
	}
}

void ADBShootWeaponBase::WeaponReloadAmmo()
{
	ADBCharacter* TOwner = GetItemOwner();
	UDBWeaponStateFiring* TFiringState = Cast<UDBWeaponStateFiring>(m_WeaponStateMachine->GetState(EWeaponState::EWeaponState_Attack));
	if (TFiringState)
	{
		GetItemOwner()->GetInventory()->GetAmmoForWeapon(TFiringState->m_CostAmmoType, m_AmmoClipSize, m_CurAmmosInClip);
	}
}

void ADBShootWeaponBase::PlayOutOfAmmoSound()
{
	UDBWeaponStateFiring* TFiringState = Cast<UDBWeaponStateFiring>(m_WeaponStateMachine->GetState(EWeaponState::EWeaponState_Attack));
	if (TFiringState)
	{
		PlayWeaponSound(TFiringState->m_RunOutOfAmmoSound);
	}
}

