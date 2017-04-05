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
	//DAWNBREAKERS_LOG_INFO("***************UDBWeaponStateFireInst::RefireTimer");
	Fire();
}

void UDBWeaponStateFireInst::Fire()
{
#ifdef DEBUG_FIRE
	FVector CamLoc;
	FRotator CamRot;
	GetWeaponOwner()->GetController()->GetPlayerViewPoint(CamLoc, CamRot);
	const FVector TraceStart = CamLoc;
	const FVector Direction = CamRot.Vector();
	const FVector TraceEnd = TraceStart + (Direction * 10000);
	FHitResult Hit(ForceInit);
	FCollisionQueryParams TraceParams(TEXT("HitTest"), true, GetWeaponOwner());
	UWorld* TCurrentWorld = GetWeaponOwner()->GetWorld();
	TCurrentWorld->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, TraceParams);
	DrawDebugLine(TCurrentWorld, TraceStart, TraceEnd, FColor::Red, false, 1.f);
	DrawDebugPoint(TCurrentWorld, Hit.Location, 10, FColor(255, 0, 255), false, 1.f);

	//FireShot(damage, loc, Rot)
	// Consume ammo.
#endif

	Super::Fire();
}
