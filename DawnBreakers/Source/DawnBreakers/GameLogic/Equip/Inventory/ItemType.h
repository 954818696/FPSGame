// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemType.generated.h"

UENUM(BlueprintType)
enum class EInventorySlot : uint8
{
	BackPack = 0,
	WaistPack = 1,

	InvisiblePack = 2,
	Superposable = 3,	// invisible.
};


UENUM(BlueprintType)
enum class EAmmoType : uint8
{
	RifleAmmo = 0,
	PistolAmmo = 1,

};
