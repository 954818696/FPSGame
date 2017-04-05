// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponStateFiring.h"


UDBWeaponStateFiring::UDBWeaponStateFiring(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_StateID = EWeaponState::EWeaponState_Attack;

	m_FireShotsPerMinute = 1.f;
	m_bIsPlayingAnim = false;
}

void UDBWeaponStateFiring::PostInitProperties()
{
	Super::PostInitProperties();

	m_TimeBetweenShots = 60.f / m_FireShotsPerMinute;
}

void UDBWeaponStateFiring::EnterWeaponState()
{
	DAWNBREAKERS_LOG_INFO("EnterWeaponState:EWeaponState_Attack %s", *GetWeapon()->GetName());
}

void UDBWeaponStateFiring::ExitWeaponState()
{
	DAWNBREAKERS_LOG_INFO("ExitWeaponState:EWeaponState_Attack %s", *GetWeapon()->GetName());
	GetWeapon()->GetWorldTimerManager().ClearTimer(TimerHandle_RefireTimer);
	StopFiringEffect();
}

bool UDBWeaponStateFiring::CanTransferTo(EWeaponState::Type NewState)
{
	if (NewState == EWeaponState::EWeaponState_Reloading ||
		NewState == EWeaponState::EWeaponState_Unequiping ||
		NewState == EWeaponState::EWeaponState_Active)
	{
		return true;
	}

	return false;
}

void UDBWeaponStateFiring::Fire()
{

	// Effect.
	PlayFiringEffect();
}

void UDBWeaponStateFiring::PlayFiringEffect()
{
	if (!m_bIsPlayingAnim)
	{
		GetWeaponOwner()->PlayAnimMontage(m_FiringAnim, 1.f, NAME_None);
		m_bIsPlayingAnim = true;
	}

	for (int32 i = 0; i < m_FiringEffects.Num(); ++i)
	{
		GetWeapon()->PlayFireShotEffectByIndex(m_FiringEffects[i]);
	}
	GetWeapon()->PlayWeaponSound(m_FiringSound);

	if (m_FiringCameraShake != nullptr)
	{
		GetWeaponOwner()->PlayCameraShake(m_FiringCameraShake, 1);
	}
}

void UDBWeaponStateFiring::StopFiringEffect()
{
	if (m_bIsPlayingAnim)
	{
		GetWeaponOwner()->StopAnimMontage(m_FiringAnim);
		m_bIsPlayingAnim = false;
	}
	for (int32 i = 0; i < m_FiringEffects.Num(); ++i)
	{
		GetWeapon()->StopFireShotEffectByIndex(m_FiringEffects[i]);
	}
}

