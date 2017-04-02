// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "WeaponImpactEffect.generated.h"

UCLASS(Abstract, Blueprintable)
class DAWNBREAKERS_API AWeaponImpactEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponImpactEffect();

	virtual void PostInitializeComponents() override;

protected:
	UParticleSystem* GetImpactEffect(EPhysicalSurface SurfaceType) const;

	USoundBase* GetImpactSound(EPhysicalSurface SurfaceType) const;

	UMaterial* GetImpactDecal(EPhysicalSurface SurfaceType) const;

public:
	FHitResult m_SurfaceHit;

protected:
	UPROPERTY(EditDefaultsOnly, Category = Effects)
	UParticleSystem* m_DefaultFX;

	UPROPERTY(EditDefaultsOnly, Category = Effects)
	UParticleSystem* m_HumanFleshFX;

	UPROPERTY(EditDefaultsOnly, Category = Sounds)
	USoundBase* m_DefaultSound;

	UPROPERTY(EditDefaultsOnly, Category = Sounds)
	USoundBase* m_HumanFleshSound;

	UPROPERTY(EditDefaultsOnly, Category = Decal)
	UMaterial* m_DefaultDecalMaterial;

	UPROPERTY(EditDefaultsOnly, Category = Decal)
	float m_DecalSize;

	UPROPERTY(EditDefaultsOnly, Category = Decal)
	float m_DecalLifeSpan;
};
