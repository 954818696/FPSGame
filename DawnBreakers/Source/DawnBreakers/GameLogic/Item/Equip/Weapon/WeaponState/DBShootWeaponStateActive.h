// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameLogic/Item/Equip/Weapon/WeaponState/DBWeaponStateActive.h"
#include "DBShootWeaponStateActive.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API UDBShootWeaponStateActive : public UDBWeaponStateActive
{
	GENERATED_BODY()
	
public:
	UDBShootWeaponStateActive();

	virtual void EnterWeaponState() override;

	virtual void ExitWeaponState() override;

public:
	UPROPERTY(EditDefaultsOnly, Category = Effect)
	int32 m_AfterFiringSmokeEffects;
	
};
