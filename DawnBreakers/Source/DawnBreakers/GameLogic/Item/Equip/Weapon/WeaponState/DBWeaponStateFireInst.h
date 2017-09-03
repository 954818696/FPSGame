// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameLogic/Item/Equip/Weapon/WeaponState/DBWeaponStateFiring.h"
#include "GameLogic/Item/Equip/Weapon/Effects/WeaponImpactEffect.h"
#include "DBWeaponStateFireInst.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API UDBWeaponStateFireInst : public UDBWeaponStateFiring
{
	GENERATED_UCLASS_BODY()

public:
	virtual void EnterWeaponState() override;

	virtual void ExitWeaponState() override;

	void RefireTimer();

	virtual void Fire() override;

private:
	void SpawnImpactEffects(const FHitResult& Impact);

	void DealInstDamage(const FHitResult& Impact, const FVector& ShootDir);

protected:
	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	float m_HitDamage;

	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	float m_FireBaseSpread;

	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	float m_FireSpreadIncrement;

	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	float m_FireMaxSpread;

	UPROPERTY(EditDefaultsOnly, Category = Effect)
	TSubclassOf<AWeaponImpactEffect> m_ImpactEffect;

private:
	float m_CurFireSpread;
	
};
