// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponConfig.generated.h"

namespace EAmmoType
{
	enum Type
	{
		E_Bullet		= 0,
		E_Rocket	= 1,
		E_Max,
	};

}

namespace EWeaponState
{
	enum Type
	{
		E_Idle					= 0,
		E_Firing				= 1,
		E_Reloading		= 2,
		E_Equiping			= 3,
	};
}

USTRUCT()
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	bool bInfiniteAmmo;

	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	bool bInfiniteClip;

	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	int32 MaxAmmo;

	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	int32 AmmoPerClip;

	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	int32 InitialClips;

	UPROPERTY(EditDefaultsOnly, Category = WeaponStat)
	float TimeBetweenShots;

	UPROPERTY(EditDefaultsOnly, Category = WeaponStat)
	float NoAnimReloadDuration;

	FWeaponData()
	{
		bInfiniteAmmo = false;
		bInfiniteClip = false;
		MaxAmmo = 120;
		AmmoPerClip = 30;
		InitialClips = 4;
		TimeBetweenShots = 0.2f;
		NoAnimReloadDuration = 1.0f;
	}
};

USTRUCT()
struct FWeaponAnim
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = WeaponAnimation)
	UAnimMontage* Idle;

	UPROPERTY(EditDefaultsOnly, Category = WeaponAnimation)
	UAnimMontage* StartFire;

	UPROPERTY(EditDefaultsOnly, Category = WeaponAnimation)
	UAnimMontage* Reload;

	UPROPERTY(EditDefaultsOnly, Category = WeaponAnimation)
	UAnimMontage* Equip;

	UPROPERTY(EditDefaultsOnly, Category = WeaponAnimation)
	UAnimMontage* UnEquip;
};


USTRUCT()
struct FWeaponSFX
{
	GENERATED_USTRUCT_BODY()
};

USTRUCT()
struct FWeaponVFX
{
	GENERATED_USTRUCT_BODY()
};




