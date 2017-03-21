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
