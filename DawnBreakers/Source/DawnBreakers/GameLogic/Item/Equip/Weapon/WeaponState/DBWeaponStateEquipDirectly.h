// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameLogic/Item/Equip/Weapon/WeaponState/DBWeaponStateBase.h"
#include "DBWeaponStateEquipDirectly.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API UDBWeaponStateEquipDirectly : public UDBWeaponStateBase
{
	GENERATED_UCLASS_BODY()
	
public:
	virtual void InitState() override;

	virtual void EnterWeaponState() override;

	virtual void ExitWeaponState() override;

	virtual bool IsHandled() override;

	virtual bool CanTransferTo(EWeaponState::Type NewState) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	UAnimMontage* m_EquipDirectlyAnim;

	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	USoundCue* m_EquipDirectlySound;

private:
	void OnEquipDirectlyAnimFinish();

	FDelegateHandle EquipDirectlyAnimFinishHandle;
	
};
