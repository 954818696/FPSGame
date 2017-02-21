// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponStateBase.h"



ADBWeaponBase* UDBWeaponStateBase::GetWeapon()
{
	UDBWeaponStateMachine* TWeaponStateMachine = GetOuterUDBWeaponStateMachine();
	if (TWeaponStateMachine)
	{
		return TWeaponStateMachine->GetOuterADBWeaponBase();
	}

	return nullptr;
}
