// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponConfig.generated.h"



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


