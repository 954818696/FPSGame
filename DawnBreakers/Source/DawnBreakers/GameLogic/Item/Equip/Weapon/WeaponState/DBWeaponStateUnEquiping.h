// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DBWeaponStateBase.h"
#include "DBWeaponStateUnEquiping.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API UDBWeaponStateUnEquiping : public UDBWeaponStateBase
{
	GENERATED_UCLASS_BODY()
	
public:
	virtual void EnterWeaponState() override;

	virtual void ExitWeaponState() override;

	virtual bool CanTransferTo(EWeaponState::Type NewState) override;

	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	UAnimMontage* m_UnEquipAnim;

	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	USoundBase* m_UnEquipSound;

private:
	void OnUnEquipAnimFinish();
	void OnAttachWeaponToInventory();
};
