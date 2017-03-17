// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DBWeaponStateBase.h"
#include "DBWeaponStateFiring.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API UDBWeaponStateFiring : public UDBWeaponStateBase
{
	GENERATED_UCLASS_BODY()

public:
	virtual void EnterWeaponState() override;

	virtual void ExitWeaponState() override;

	virtual bool CanTransferTo(EWeaponState::Type NewState) override;

	virtual void RefireTimer();

	void Fire();

	virtual void PlayFiringEffect();
	
	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	UAnimMontage* m_FiringAnim;

	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	USoundBase* m_FiringSound;

	UPROPERTY(EditAnywhere,  Category = WeaponState)
	TArray<UParticleSystemComponent*> m_FiringEffects;
	
};
