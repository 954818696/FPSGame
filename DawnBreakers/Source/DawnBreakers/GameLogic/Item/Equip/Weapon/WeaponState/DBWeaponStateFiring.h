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

	virtual void StopFiringEffect();
	
	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	float m_FireShotsPerMinute;

	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	UAnimMontage* m_FiringAnim;

	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	USoundBase* m_FiringSound;

	UPROPERTY(BlueprintReadWrite ,EditDefaultsOnly,  Category = WeaponState)
	TArray<int32> m_FiringEffects;

protected:
	bool m_bIsPlayingAnim;

	float m_TimeBetweenShots;

	FTimerHandle TimerHandle_RefireTimer;
};
