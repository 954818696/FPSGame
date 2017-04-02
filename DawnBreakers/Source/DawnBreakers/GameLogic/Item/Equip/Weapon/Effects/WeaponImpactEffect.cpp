// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "WeaponImpactEffect.h"

AWeaponImpactEffect::AWeaponImpactEffect()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AWeaponImpactEffect::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	UPhysicalMaterial* THitPhysicalMat = m_SurfaceHit.PhysMaterial.Get();
	EPhysicalSurface THitSurfaceType = UPhysicalMaterial::DetermineSurfaceType(THitPhysicalMat);

	UParticleSystem* TImpactFX = GetImpactEffect(THitSurfaceType);
	if (TImpactFX)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, TImpactFX, GetActorLocation(), GetActorRotation());
	}

	USoundBase* TImpactSound = GetImpactSound(THitSurfaceType);
	if (TImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, TImpactSound, GetActorLocation());
	}

	UMaterial* TDecalMat = GetImpactDecal(THitSurfaceType);
	if (TDecalMat)
	{
		FRotator TRandomDecalRotation = m_SurfaceHit.ImpactNormal.Rotation();
		TRandomDecalRotation.Roll = FMath::FRandRange(-180.0f, 180.0f);

		UGameplayStatics::SpawnDecalAttached(TDecalMat, FVector(m_DecalSize, m_DecalSize, 1.0f),
																			m_SurfaceHit.Component.Get(), m_SurfaceHit.BoneName,
																			m_SurfaceHit.ImpactPoint, TRandomDecalRotation, EAttachLocation::KeepWorldPosition,
																			m_DecalLifeSpan);
	}

}

UParticleSystem* AWeaponImpactEffect::GetImpactEffect(EPhysicalSurface SurfaceType) const
{
	switch (SurfaceType)
	{
	case SURFACE_DEFAULT:
		return m_DefaultFX;
	case SURFACE_HUMAN_FLESH:
		return m_HumanFleshFX;
	default:
		return nullptr;
	}

	return nullptr;
}

USoundBase* AWeaponImpactEffect::GetImpactSound(EPhysicalSurface SurfaceType) const
{
	switch (SurfaceType)
	{
	case SURFACE_DEFAULT:
		return m_DefaultSound;
	case SURFACE_HUMAN_FLESH:
		return m_HumanFleshSound;
	default:
		return nullptr;
	}

	return nullptr;
}

UMaterial* AWeaponImpactEffect::GetImpactDecal(EPhysicalSurface SurfaceType) const
{
	switch (SurfaceType)
	{
	case SURFACE_DEFAULT:
		return m_DefaultDecalMaterial;
	default:
		return nullptr;
	}

	return nullptr;
}

