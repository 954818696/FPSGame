// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemType.generated.h"

UENUM(BlueprintType)
enum class EItemAttachToTargetType : uint8
{
	AttachToNone			= 0,
	AttachToCharacter	= 1,		// 人物装备此“武器”时的挂载类型
	AttachToInventory	= 2,		// 放入背包时的挂载类型
	AttachToWeapon		= 3,		// 武器挂件挂载类型
};

USTRUCT(BlueprintType)
struct FItemAttachToTargetSocket
{
	GENERATED_USTRUCT_BODY()

	FItemAttachToTargetSocket()
	{
		AttachToTargetType = EItemAttachToTargetType::AttachToNone;
	}

	UPROPERTY(EditAnywhere, Category = ADBInventoryItemBase)
	EItemAttachToTargetType AttachToTargetType;

	UPROPERTY(EditAnywhere, Category = ADBInventoryItemBase)
	FName AttachToParentSocketName;
};

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
