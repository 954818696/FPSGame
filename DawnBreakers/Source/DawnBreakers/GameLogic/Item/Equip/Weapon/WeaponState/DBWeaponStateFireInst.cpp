// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponStateFireInst.h"

UDBWeaponStateFireInst::UDBWeaponStateFireInst(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}



void UDBWeaponStateFireInst::EnterWeaponState()
{
	Fire();
	GetWeapon()->GetWorldTimerManager().SetTimer(TimerHandle_RefireTimer, this, &UDBWeaponStateFireInst::RefireTimer, m_TimeBetweenShots, true);
}

void UDBWeaponStateFireInst::RefireTimer()
{
	Fire();
}

void UDBWeaponStateFireInst::Fire()
{

	FVector CamLoc;
	FRotator CamRot;
	const FVector TraceStart = GetWeapon()->GetMeshComp()->GetSocketLocation(FName(TEXT("MuzzleSocket")));
	const FVector Direction = GetWeaponOwner()->GetFiringDirection()
	const FVector TraceEnd = TraceStart + Direction * m_FireRange;
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
