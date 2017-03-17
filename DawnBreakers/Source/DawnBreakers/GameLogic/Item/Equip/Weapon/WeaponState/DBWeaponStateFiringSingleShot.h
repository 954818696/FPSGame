// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameLogic/Item/Equip/Weapon/WeaponState/DBWeaponStateFiring.h"
#include "DBWeaponStateFiringSingleShot.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API UDBWeaponStateFiringSingleShot : public UDBWeaponStateFiring
{
	GENERATED_UCLASS_BODY()
	
public:
	virtual void EnterWeaponState() override;

	virtual void RefireTimer() override;
	

};
