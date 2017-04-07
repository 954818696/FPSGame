// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DBWeaponStateBase.h"
#include "GameLogic/Item/Equip/Weapon/Effects/WeaponImpactEffect.h"
#include "GameLogic/Item/Equip/Inventory/ItemType.h"
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

	virtual bool CanTransferTo(EWeaponState::Type NewState, UDBWeaponStateBase* State) override;

	virtual void Fire();

	virtual void PlayFiringEffect();

	virtual void StopFiringEffect();

	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	bool m_bAutomaticMode;

	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	EAmmoType m_CostAmmoType;
	
	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	TSubclassOf<class UDamageType> m_DamageType;

	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	float m_HitDamage;

	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	float m_FireShotsPerMinute;

	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	float m_FireRange;

	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	UAnimMontage* m_FiringAnim;

	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	USoundBase* m_FiringSound;

	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	USoundBase* m_RunOutOfAmmoSound;

	UPROPERTY(BlueprintReadWrite ,EditDefaultsOnly,  Category = Effect)
	TArray<int32> m_FiringEffects;

	UPROPERTY(EditDefaultsOnly, Category = Effect)
	TSubclassOf<AWeaponImpactEffect> m_ImpactEffect;

	UPROPERTY(EditDefaultsOnly, Category = Effect)
	TSubclassOf<UCameraShake> m_FiringCameraShake;

protected:
	bool m_bIsPlayingAnim;

	float m_TimeBetweenShots;

	FTimerHandle TimerHandle_RefireTimer;

	class ADBShootWeaponBase* m_Weapon;
};
