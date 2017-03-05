// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DBWeaponStateBase.h"
#include "DBWeaponStateReload.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API UDBWeaponStateReload : public UDBWeaponStateBase
{
	GENERATED_UCLASS_BODY()
	
public:

	virtual void EnterWeaponState() override;

	virtual void ExitWeaponState() override;

	virtual bool CanTransferTo(EWeaponState::Type NewState);

protected:
	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	UAnimMontage* m_ReloadAnim;

	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	USoundCue* m_ReloadSound;
	
private:
	void OnReloadAnimFinish();

};
