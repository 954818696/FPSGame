// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponBase.h"

ADBWeaponBase::ADBWeaponBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	m_CurrentFireMode(0)
{
	m_AudioComp = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("WeaponSoundComp"));
	m_AudioComp->bAutoActivate = false;
	m_AudioComp->bAutoDestroy = false;
	m_AudioComp->SetupAttachment(RootComponent);

	m_WeaponStateMachine = ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateMachine>(this, TEXT("WeaponStateMachine"), false);
}

void ADBWeaponBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	m_WeaponStateMachine->InitStateMachine();
}

void ADBWeaponBase::OnEquip(bool bEquipedWeaponFromInventory)
{
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

void ADBWeaponBase::OnStartFire()
{
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_Firing);
}

void ADBWeaponBase::OnStopFire()
{
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_Active);
}

void ADBWeaponBase::PlayWeaponSound(USoundBase* SoundToPlay)
{
	m_AudioComp->SetSound(SoundToPlay);
	m_AudioComp->Play();
}

bool ADBWeaponBase::IsInState(EWeaponState::Type WeaponState) const
{
	if (m_WeaponStateMachine->IsInState(WeaponState))
	{
		return true;
	}

	return false;
}

int32 ADBWeaponBase::GetWeaponHoldStanceType()
{
	return (int32)m_WeaponHoldType;
}
