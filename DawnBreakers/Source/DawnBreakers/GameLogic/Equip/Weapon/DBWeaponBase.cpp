// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponBase.h"

ADBWeaponBase::ADBWeaponBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_SkeletalMeshComp = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("SkeletalMesh"));
	m_SkeletalMeshComp->SetVisibility(true);
	m_SkeletalMeshComp->SetCollisionObjectType(ECC_WorldDynamic);
	m_SkeletalMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	m_SkeletalMeshComp->SetSimulatePhysics(true);
	m_MeshComp = m_SkeletalMeshComp;
	RootComponent = m_SkeletalMeshComp;
	//m_SkeletalMeshComp->SetupAttachment(m_SceneComponentRoot);

	m_WeaponStateMachine = ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateMachine>(this, TEXT("WeaponStateMachine"), false);
}

void ADBWeaponBase::OnEquip()
{

	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_Equiping);
}

void ADBWeaponBase::OnUnEquip()
{
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_Unequiping);
}

void ADBWeaponBase::OnSwitchMode()
{
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_SwitchMode);
}

void ADBWeaponBase::OnReload()
{
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_Equiping);
}

void ADBWeaponBase::OnStartFire()
{
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_Firing);
}

void ADBWeaponBase::OnStopFire()
{
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_Active);
}

bool ADBWeaponBase::IsInState(EWeaponState::Type WeaponState) const
{
	if (m_WeaponStateMachine->IsInState(WeaponState))
		return true;

	return false;
}

//void ADBWeaponBase::SetInteractFocus()
//{
//	m_SkeletalMeshComp->SetRenderCustomDepth(true);
//}
//
//void ADBWeaponBase::LoseInteractFocus()
//{
//	m_SkeletalMeshComp->SetRenderCustomDepth(false);
//}
