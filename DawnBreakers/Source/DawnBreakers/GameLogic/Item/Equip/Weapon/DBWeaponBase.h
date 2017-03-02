// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameLogic/Item/Equip/Inventory/DBInventoryItemBase.h"
#include "WeaponState/DBWeaponStateMachine.h"
#include "DBWeaponConfig.h"
#include "DBWeaponBase.generated.h"



DECLARE_EVENT(ADBWeaponBase, FEquipAnimFinishEvent)
DECLARE_EVENT(ADBWeaponBase, FUnEquipAnimFinishEvent)

/**
 * 
 */
UCLASS(Abstract)
class DAWNBREAKERS_API ADBWeaponBase : public ADBInventoryItemBase
{
	GENERATED_UCLASS_BODY()

public:

	virtual void PostInitProperties() override;

	virtual void OnEquip(bool bEquipedWeaponFromInventory);

	virtual void OnUnEquip();

	virtual void OnSwitchMode();

	virtual void OnReload();

	virtual void OnStartFire();

	virtual void OnStopFire();

	void PlayWeaponSound(USoundCue* SoundToPlay);

	FORCEINLINE int32 GetCurrentFireMode() const { return m_CurrentFireMode;}

	FORCEINLINE bool IsInState(EWeaponState::Type WeaponState) const;

	FEquipAnimFinishEvent& OnEquipAnimFinish() { return EquipAnimFinishEvent; }
	FUnEquipAnimFinishEvent& OnUnEquipAnimFinish() { return UnEquipAnimFinishEvent; }
	
protected:

	/** Weapon State Machine */
	UPROPERTY(EditDefaultsOnly, Category = WeaponState, NoClear)
	class UDBWeaponStateMachine* m_WeaponStateMachine;

	/* Plays the idle, wandering or hunting sound */
	UPROPERTY(VisibleAnywhere, Category = "Sound")
	UAudioComponent* m_AudioComp;

	EWeaponTypeForEquipAnim m_WeaponHoldType;

	int32 m_CurrentFireMode;

private:
	FEquipAnimFinishEvent		EquipAnimFinishEvent;
	FUnEquipAnimFinishEvent UnEquipAnimFinishEvent;
};
