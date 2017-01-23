// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameLogic/Equip/Inventory/DBInventoryItemBase.h"
#include "WeaponState/DBWeaponStateMachine.h"
#include "DBWeaponBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DAWNBREAKERS_API ADBWeaponBase : public ADBInventoryItemBase
{
	GENERATED_UCLASS_BODY()

public:
	virtual void PostInitializeComponents() override;

	virtual void OnEquip();

	virtual void OnUnEquip();

	virtual void OnSwitchMode();

	virtual void OnReload();

	virtual void OnStartFire();

	virtual void OnStopFire();

	FORCEINLINE int32 GetCurrentFireMode() const
	{
		return m_CurrentFireMode;
	}

	FORCEINLINE bool IsInState(EWeaponState::Type WeaponState) const;

	virtual void SetInteractFocus() override;

	virtual void LoseInteractFocus() override;

	UPROPERTY(VisibleAnywhere, Category = "ADBInventoryItemBase")
		USkeletalMeshComponent* m_SkeletalMeshComp;
	
protected:
	//UPROPERTY(VisibleAnywhere, Category = "ADBInventoryItemBase")
	//USkeletalMeshComponent* m_SkeletalMeshComp;

	/** Weapon State Machine */
	UPROPERTY(EditDefaultsOnly, Category = WeaponState, NoClear)
	class UDBWeaponStateMachine* m_WeaponStateMachine;

	int32 m_CurrentFireMode;
};
