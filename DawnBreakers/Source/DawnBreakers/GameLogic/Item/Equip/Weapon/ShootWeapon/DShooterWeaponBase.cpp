// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DShooterWeaponBase.h"


ADShooterWeaponBase::ADShooterWeaponBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	m_bPendingReload = false;
}

void ADShooterWeaponBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void ADShooterWeaponBase::Destroyed()
{
	Super::Destroyed();

}

void ADShooterWeaponBase::StartFire()
{

}

void ADShooterWeaponBase::StopFire()
{

}

void ADShooterWeaponBase::StartReload()
{

}

void ADShooterWeaponBase::StopReload()
{

}

void ADShooterWeaponBase::OnEquip()
{

}

void ADShooterWeaponBase::OnEquipFinished()
{
	//SetWeaponState(EWeaponState::E_Idle);
}

//void ADShooterWeaponBase::SetWeaponState(EWeaponState::Type NewWeaponState)
//{
//	const EWeaponState::Type PrevWeaponState = m_WeaponState;
//
//	if (PrevWeaponState == EWeaponState::E_Firing && NewWeaponState != EWeaponState::E_Firing)
//	{
//		DAWNBREAKERS_LOG_INFO("SetWeaponState Start Fire");
//
//	}
//	else if (PrevWeaponState != EWeaponState::E_Firing && NewWeaponState == EWeaponState::E_Firing)
//	{
//		DAWNBREAKERS_LOG_INFO("SetWeaponState Stop Fire");
//	}
//
//	m_WeaponState = NewWeaponState;
//}

//EWeaponState::Type ADShooterWeaponBase::GetWeaponState() const
//{
//	return m_WeaponState;
//}

void ADShooterWeaponBase::HandleFire()
{
	GetWorldTimerManager().SetTimer(TimeHandle_HandleFiring, this, &ADShooterWeaponBase::HandleFire, m_WeaponConfig.TimeBetweenShots, false);
}

void ADShooterWeaponBase::SimulateWeaponFire()
{
	
}

