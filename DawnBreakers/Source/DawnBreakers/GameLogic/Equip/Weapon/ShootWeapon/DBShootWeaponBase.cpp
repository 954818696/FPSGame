// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBShootWeaponBase.h"
#include "GameLogic/Equip/Weapon/ShootWeapon/WeaponState/DBWeaponStateMachine.h"



ADBShootWeaponBase::ADBShootWeaponBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_FakeSkeletalMeshPhysicBoxComp = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BoxCollsion"));
	m_FakeSkeletalMeshPhysicBoxComp->SetupAttachment(m_StaticMeshComp);
	m_FakeSkeletalMeshPhysicBoxComp->SetCollisionObjectType(ECC_WorldDynamic);

	m_SkeletalMeshComp = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("SkeletalMesh"));
	m_SkeletalMeshComp->SetVisibility(true);
	m_SkeletalMeshComp->SetupAttachment(m_FakeSkeletalMeshPhysicBoxComp);

	m_WeaponStateMachine = ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateMachine>(this, TEXT("WeaponStateMachine"), false);
}

void ADBShootWeaponBase::OnStartFire()
{

}

void ADBShootWeaponBase::OnStopFire()
{

}

void ADBShootWeaponBase::SetInteractFocus()
{
	m_SkeletalMeshComp->SetRenderCustomDepth(true);
}

void ADBShootWeaponBase::LoseInteractFocus()
{
	m_SkeletalMeshComp->SetRenderCustomDepth(false);
}
