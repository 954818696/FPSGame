// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameLogic/Equip/Inventory/DBInventoryItemBase.h"
#include "DBWeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API ADBWeaponBase : public ADBInventoryItemBase
{
	GENERATED_UCLASS_BODY()
	
public:

	void OnStartFire();

	void OnStopFire();

	FORCEINLINE int32 GetCurrentFireMode() const
	{
		return m_CurrentFireMode;
	}
	
protected:
	/** Weapon State Machine */
	UPROPERTY(EditDefaultsOnly, Category = WeaponState, NoClear)
	class UDBWeaponStateMachine* m_WeaponStateMachine;

	int32 m_CurrentFireMode;



};
