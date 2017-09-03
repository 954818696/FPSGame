// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponStateFireInst.h"

UDBWeaponStateFireInst::UDBWeaponStateFireInst(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	m_FireBaseSpread(5.f),
	m_FireSpreadIncrement(0.15f),
	m_FireMaxSpread(3.f),
	m_CurFireSpread(0.f)
{
}

void UDBWeaponStateFireInst::EnterWeaponState()
{
	Super::EnterWeaponState();

	Fire();
	m_Weapon->GetWorldTimerManager().SetTimer(TimerHandle_RefireTimer, this, &UDBWeaponStateFireInst::RefireTimer, m_TimeBetweenShots, true);
}

void UDBWeaponStateFireInst::ExitWeaponState()
{
	Super::ExitWeaponState();

	m_CurFireSpread = 0.f;
}

void UDBWeaponStateFireInst::RefireTimer()
{
	Fire();
}

void UDBWeaponStateFireInst::Fire()
{
	// Calculate Direction and Firing location.
	float TSpread = m_FireBaseSpread + m_CurFireSpread;
	m_CurFireSpread = FMath::Min(m_FireMaxSpread, m_CurFireSpread + m_FireSpreadIncrement);
	const int32 TRandomSeed = FMath::Rand();
	FRandomStream TWeaponRandomStream(TRandomSeed);
	const float TConeHalfAngle = FMath::DegreesToRadians(TSpread * 0.5f);
	const FVector TDirection = GetWeaponOwner()->GetFiringDirection();
	const FVector FiringDir = TWeaponRandomStream.VRandCone(TDirection, TConeHalfAngle, TConeHalfAngle);
	const FVector TraceStart = m_Weapon->GetMeshComp()->GetSocketLocation(FName(TEXT("Muzzle")));
	const FVector TraceEnd = TraceStart + FiringDir * m_FireRange;

	// Trace parameter Set and Perform trace to retrieve hit info.
	static FName TWeaponFireTag = FName(TEXT("WeaponTrace"));
	FCollisionQueryParams TraceParams(TWeaponFireTag, true, GetWeaponOwner());
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = true;
	UWorld* TCurrentWorld = GetWeapon()->GetWorld();
	FHitResult Hit(ForceInit);
	TCurrentWorld->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, COLLISION_WEAPON_INST, TraceParams);

	// Impact
	if (Hit.bBlockingHit)
	{
		SpawnImpactEffects(Hit);
	}

	DealInstDamage(Hit, FiringDir);

#ifdef DEBUG_FIRE
	DrawDebugLine(TCurrentWorld, TraceStart, TraceEnd, FColor::Red, false, 1.f);
	DrawDebugPoint(TCurrentWorld, Hit.Location, 10, FColor(255, 0, 255), false, 1.f);
#endif

	Super::Fire();
}

void UDBWeaponStateFireInst::SpawnImpactEffects(const FHitResult& Impact)
{
	if (m_ImpactEffect && Impact.bBlockingHit)
	{
		FTransform const SpawnTransform(Impact.ImpactNormal.Rotation(), Impact.ImpactPoint);
		AWeaponImpactEffect* ImpactEffectActor = m_Weapon->GetWorld()->SpawnActorDeferred<AWeaponImpactEffect>(m_ImpactEffect, SpawnTransform);
		if (ImpactEffectActor)
		{
			ImpactEffectActor->m_SurfaceHit = Impact;
			UGameplayStatics::FinishSpawningActor(ImpactEffectActor, SpawnTransform);
		}
	}
}

void UDBWeaponStateFireInst::DealInstDamage(const FHitResult& Impact, const FVector& ShootDir)
{
	float ActualHitDamage = m_HitDamage;
	if (m_DamageType == nullptr)
	{
		return;
	}

	UDBDamageType* DmgType = Cast<UDBDamageType>(m_DamageType->GetDefaultObject());
	UPhysicalMaterial * PhysMat = Impact.PhysMaterial.Get();
	if (PhysMat && DmgType)
	{
		if (PhysMat->SurfaceType == SURFACE_ZOMBIEHEAD)
		{
			ActualHitDamage *= DmgType->GetHeadDamageModifier();
		}
		else if (PhysMat->SurfaceType == SURFACE_ZOMBIELIMB)
		{
			ActualHitDamage *= DmgType->GetLimbDamageModifier();
		}
	}

	FPointDamageEvent PointDmg;
	PointDmg.DamageTypeClass = m_DamageType;
	PointDmg.HitInfo = Impact;
	PointDmg.ShotDirection = ShootDir;
	PointDmg.Damage = ActualHitDamage;

	if (Impact.GetActor())
	{
		Impact.GetActor()->TakeDamage(PointDmg.Damage, PointDmg, GetWeaponOwner()->GetController(), GetWeapon());
	}
}
