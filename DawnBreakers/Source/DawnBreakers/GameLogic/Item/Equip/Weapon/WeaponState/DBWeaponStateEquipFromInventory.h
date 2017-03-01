// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameLogic/Item/Equip/Weapon/WeaponState/DBWeaponStateBase.h"
#include "DBWeaponStateEquipFromInventory.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API UDBWeaponStateEquipFromInventory : public UDBWeaponStateBase
{
	GENERATED_UCLASS_BODY()
	
public:
	virtual void InitState() override;

	virtual void EnterWeaponState() override;

	virtual void ExitWeaponState() override;

	virtual bool CanTransferTo(EWeaponState::Type NewState);

protected:
	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	UAnimMontage* m_EquipAnim;

	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	USoundCue* m_EquipSound;

private:
	void OnEquipAnimFinish();

	FDelegateHandle EquipAnimFinishHandle;
};
