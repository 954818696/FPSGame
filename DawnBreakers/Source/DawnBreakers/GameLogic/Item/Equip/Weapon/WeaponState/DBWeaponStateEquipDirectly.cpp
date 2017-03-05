// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponStateEquipDirectly.h"


UDBWeaponStateEquipDirectly::UDBWeaponStateEquipDirectly(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_StateID = EWeaponState::EWeaponState_EquipingDirectly;
}

void UDBWeaponStateEquipDirectly::InitState()
{
	if (!EquipDirectlyAnimFinishHandle.IsValid())
	{
		EquipDirectlyAnimFinishHandle = GetWeapon()->OnWeaponAnimFinish().AddUObject(this, &UDBWeaponStateEquipDirectly::OnEquipDirectlyAnimFinish);
	}
}

void UDBWeaponStateEquipDirectly::EnterWeaponState()
{
	DAWNBREAKERS_LOG_INFO("EnterWeaponState:EWeaponState_EquipingDirectly");
	m_bHandled = false;

	ADBCharacter *TCharacter = GetWeaponOwner();
	if (TCharacter)
	{
		TCharacter->PlayAnimMontage(m_EquipDirectlyAnim, 1.f, NAME_None);
		GetWeapon()->PlayWeaponSound(m_EquipDirectlySound);
	}
}

void UDBWeaponStateEquipDirectly::ExitWeaponState()
{
	DAWNBREAKERS_LOG_INFO("ExitWeaponState:EWeaponState_EquipingDirectly");
}

bool UDBWeaponStateEquipDirectly::IsHandled()
{
	return true;
}

bool UDBWeaponStateEquipDirectly::CanTransferTo(EWeaponState::Type NewState)
{
	if (NewState == EWeaponState::EWeaponState_Inactive  &&
		IsHandled())
	{
		return true;
	}

	return false;
}

void UDBWeaponStateEquipDirectly::OnEquipDirectlyAnimFinish()
{

	ADBWeaponBase* TWeapon = GetWeapon();
	if (TWeapon)
	{
		m_bHandled = true;
		ADBCharacter* TOwner = Cast<ADBCharacter>(TWeapon->GetOwner());
		USceneComponent* TParentComp = TOwner->GetMesh();
		if (TParentComp)
		{
			TWeapon->AttachToTarget(EItemAttachToTargetType::AttachToCharacter, TParentComp);
		}
		TWeapon->PlayWeaponSound(m_EquipDirectlySound);
		TOwner->SetHoldWeapon(TWeapon);
		GetOuterUDBWeaponStateMachine()->GotoState(EWeaponState::EWeaponState_Active);
	}
}

