// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameLogic/Item/Equip/Weapon/WeaponState/DBWeaponStateBase.h"
#include "DBWeaponStateEquipDirectly.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API UDBWeaponStateEquipDirectly : public UDBWeaponStateBase
{
	GENERATED_UCLASS_BODY()
	
public:
	virtual void EnterWeaponState();

	virtual void ExitWeaponState();

	virtual bool IsHandled();
	
};
