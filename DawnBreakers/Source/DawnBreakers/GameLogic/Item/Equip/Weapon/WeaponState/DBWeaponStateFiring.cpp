// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponStateFiring.h"


UDBWeaponStateFiring::UDBWeaponStateFiring(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_StateID = EWeaponState::EWeaponState_Firing;
}

void UDBWeaponStateFiring::EnterWeaponState()
{
	DAWNBREAKERS_LOG_INFO("EnterWeaponState:EWeaponState_Firing %s", *GetWeapon()->GetName());
}

void UDBWeaponStateFiring::ExitWeaponState()
{
	DAWNBREAKERS_LOG_INFO("ExitWeaponState:EWeaponState_Firing %s", *GetWeapon()->GetName());
}

bool UDBWeaponStateFiring::CanTransferTo(EWeaponState::Type NewState)
{
	if (NewState == EWeaponState::EWeaponState_Reloading ||
		NewState == EWeaponState::EWeaponState_Unequiping)
	{
		return true;
	}

	return false;
}

void UDBWeaponStateFiring::RefireTimer()
{

}

void UDBWeaponStateFiring::Fire()
{
	// Consume ammo.

	// Effect.
	PlayFiringEffect();
}

void UDBWeaponStateFiring::PlayFiringEffect()
{
	
}

