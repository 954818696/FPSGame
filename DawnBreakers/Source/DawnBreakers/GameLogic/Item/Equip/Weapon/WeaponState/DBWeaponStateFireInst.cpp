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
	GetWeapon()->GetWorldTimerManager().SetTimer(TimerHandle_RefireTimer, this, &UDBWeaponStateFireInst::RefireTimer, m_TimeBetweenShots, true);
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
	const FVector TraceStart = GetWeapon()->GetMeshComp()->GetSocketLocation(FName(TEXT("Muzzle")));
	const FVector TraceEnd = TraceStart + FiringDir * m_FireRange;

	// Trace parameter Set and Perform trace to retrieve hit info.
	static FName TWeaponFireTag = FName(TEXT("WeaponTrace"));
	FCollisionQueryParams TraceParams(TWeaponFireTag, true, GetWeaponOwner());
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = true;
	UWorld* TCurrentWorld = GetWeaponOwner()->GetWorld();
	FHitResult Hit(ForceInit);
	TCurrentWorld->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, COLLISION_WEAPON_INST, TraceParams);

#ifdef DEBUG_FIRE
	DrawDebugLine(TCurrentWorld, TraceStart, TraceEnd, FColor::Red, false, 1.f);
	DrawDebugPoint(TCurrentWorld, Hit.Location, 10, FColor(255, 0, 255), false, 1.f);
#endif

	//FireShot(damage, loc, Rot)



	Super::Fire();
}
