// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponStateBase.h"

UDBWeaponStateBase::UDBWeaponStateBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	 m_bHandled(true)
{

}

ADBWeaponBase* UDBWeaponStateBase::GetWeapon()
{
	if (m_WeaponStateMachine.IsValid())
	{
		return m_WeaponStateMachine->GetOuterADBWeaponBase();
	}

	return nullptr;
}

ADBCharacter* UDBWeaponStateBase::GetWeaponOwner()
{
	ADBWeaponBase* TWeapon = GetWeapon();
	if (TWeapon)
	{
		ADBCharacter* TOwner = TWeapon->GetItemOwner();
		return TOwner;
	}

	return nullptr;
}
