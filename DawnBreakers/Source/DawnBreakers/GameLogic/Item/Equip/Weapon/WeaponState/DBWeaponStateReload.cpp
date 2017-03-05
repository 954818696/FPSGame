// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponStateReload.h"

UDBWeaponStateReload::UDBWeaponStateReload(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_StateID = EWeaponState::EWeaponState_Reloading;

}

void UDBWeaponStateReload::EnterWeaponState()
{
	DAWNBREAKERS_LOG_INFO("EnterWeaponState:EWeaponState_Reloading");
	m_bHandled = false;
	ADBCharacter* TCharacter = GetWeaponOwner();
	ADBWeaponBase* TWeapon = GetWeapon();
	if (TCharacter)
	{
		TWeapon->OnWeaponAnimFinish().Clear();
		TWeapon->OnWeaponAnimFinish().AddUObject(this, &UDBWeaponStateReload::OnReloadAnimFinish);

		TCharacter->PlayAnimMontage(m_ReloadAnim, 1.f, NAME_None);
		TWeapon->PlayWeaponSound(m_ReloadSound);
	}
}

void UDBWeaponStateReload::ExitWeaponState()
{
	DAWNBREAKERS_LOG_INFO("ExitWeaponState:EWeaponState_Reloading");
	if (!IsHandled())
	{
		ADBCharacter* TCharacter = GetWeaponOwner();
		if (TCharacter)
		{
			TCharacter->StopAnimMontage(m_ReloadAnim);
		}
	}
}

bool UDBWeaponStateReload::CanTransferTo(EWeaponState::Type NewState)
{
	if (NewState == EWeaponState::EWeaponState_Unequiping || NewState == EWeaponState::EWeaponState_Inactive)
	{
		return true;
	}
	else if (IsHandled() && NewState == EWeaponState::EWeaponState_Active)
	{
		return true;
	}

	return false;
}

void UDBWeaponStateReload::OnReloadAnimFinish()
{
	m_bHandled = true;
}

