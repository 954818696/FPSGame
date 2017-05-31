// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameLogic/Item/Equip/Weapon/DBWeaponBase.h"
#include "DBShootWeaponBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract, Placeable)
class DAWNBREAKERS_API ADBShootWeaponBase : public ADBWeaponBase
{
	GENERATED_UCLASS_BODY()
	
public:
	virtual void OnReload();

	virtual void OnSwitchMode();

	virtual void OnStartFire() override;

	virtual void OnStopFire();

	void SetCurAmmosInClip(int32 AmmoAmount);

	void ConsumeAmmo(EAmmoType AmmoType, int32 CostAmount);

	void WeaponReloadAmmo();

	FORCEINLINE int32 GetAmmoClipSize() { return m_AmmoClipSize; }

private:
	void PlayOutOfAmmoSound();

protected:
	UPROPERTY(EditDefaultsOnly, Category = WeaponConfig)
	int32 m_AmmoClipSize;

	UPROPERTY(EditDefaultsOnly, Category = WeaponConfig)
	int32 m_CurAmmosInClip;
};
