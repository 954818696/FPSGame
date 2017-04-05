// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameLogic/Item/Equip/Weapon/WeaponState/DBWeaponStateFiring.h"
#include "DBWeaponStateFireInst.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API UDBWeaponStateFireInst : public UDBWeaponStateFiring
{
	GENERATED_UCLASS_BODY()

public:
	virtual void EnterWeaponState() override;

	void RefireTimer();

	virtual void Fire() override;
	
};
