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
	
protected:

	UPROPERTY(Instanced, EditDefaultsOnly, Category = "DBWeaponConfig", NoClear)
	class UDBWeaponStateMachine* m_WeaponStateMachine;

	uint8 m_FireMode;
	

};
