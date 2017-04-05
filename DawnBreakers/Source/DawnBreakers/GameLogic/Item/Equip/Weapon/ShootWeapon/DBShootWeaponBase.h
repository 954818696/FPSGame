// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameLogic/Item/Equip/Weapon/DBWeaponBase.h"
#include "DBShootWeaponBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract, NotPlaceable)
class DAWNBREAKERS_API ADBShootWeaponBase : public ADBWeaponBase
{
	GENERATED_UCLASS_BODY()
	
public:
	virtual void OnReload();

	virtual void OnSwitchMode();

	virtual void OnStopFire();

	FORCEINLINE int32 GetAmmoClipSize() { return m_AmmoClipSize; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = WeaponConfig)
	int32 m_AmmoClipSize;
};
