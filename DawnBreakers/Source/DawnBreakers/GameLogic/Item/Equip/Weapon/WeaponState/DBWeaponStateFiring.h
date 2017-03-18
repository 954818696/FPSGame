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
	virtual void PostInitProperties() override;

	virtual void EnterWeaponState() override;

	virtual void ExitWeaponState() override;

	virtual bool CanTransferTo(EWeaponState::Type NewState) override;

	virtual void RefireTimer();

	virtual void Fire();

	virtual void PlayFiringEffect();
	
	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	float m_FireShotsPersecond;

	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	UAnimMontage* m_FiringAnim;

	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	USoundBase* m_FiringSound;

	UPROPERTY(EditDefaultsOnly,  Category = WeaponState)
	TArray<UParticleSystemComponent*> m_FiringEffects;

protected:
	float m_TimeBetweenShots;

	FTimerHandle TimerHandle_RefireTimer;
};
