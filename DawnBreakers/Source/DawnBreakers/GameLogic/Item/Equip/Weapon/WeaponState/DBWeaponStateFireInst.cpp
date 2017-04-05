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
	float TSpread = m_FireBaseSpread + m_CurFireSpread;
	m_CurFireSpread = FMath::Min(m_FireMaxSpread, m_CurFireSpread + m_FireSpreadIncrement);
	const int32 TRandomSeed = FMath::Rand();
	FRandomStream TWeaponRandomStream(TRandomSeed);
	const float TConeHalfAngle = FMath::DegreesToRadians(TSpread * 0.5f);
	const FVector TDirection = GetWeaponOwner()->GetFiringDirection();
	const FVector FiringDir = TWeaponRandomStream.VRandCone(TDirection, TConeHalfAngle, TConeHalfAngle);

	const FVector TraceStart = GetWeapon()->GetMeshComp()->GetSocketLocation(FName(TEXT("Muzzle")));
	const FVector TraceEnd = TraceStart + FiringDir * m_FireRange;
	
	FHitResult Hit(ForceInit);
	FCollisionQueryParams TraceParams(TEXT("HitTest"), true, GetWeaponOwner());
	UWorld* TCurrentWorld = GetWeaponOwner()->GetWorld();
	TCurrentWorld->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, TraceParams);

#ifdef DEBUG_FIRE
	DrawDebugLine(TCurrentWorld, TraceStart, TraceEnd, FColor::Red, false, 1.f);
	DrawDebugPoint(TCurrentWorld, Hit.Location, 10, FColor(255, 0, 255), false, 1.f);
#endif

	//FireShot(damage, loc, Rot)
	// Consume ammo.


	Super::Fire();
}
