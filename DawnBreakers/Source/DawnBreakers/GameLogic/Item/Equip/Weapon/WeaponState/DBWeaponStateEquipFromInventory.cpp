// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponStateEquipFromInventory.h"



UDBWeaponStateEquipFromInventory::UDBWeaponStateEquipFromInventory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_StateID = EWeaponState::EWeaponState_EquipingFromInventory;

}

void UDBWeaponStateEquipFromInventory::InitState()
{
	if (!EquipAnimFinishHandle.IsValid())
	{
		EquipAnimFinishHandle = GetWeapon()->OnWeaponAnimFinish().AddUObject(this, &UDBWeaponStateEquipFromInventory::OnEquipAnimFinish);
	}
}

void UDBWeaponStateEquipFromInventory::EnterWeaponState()
{
	DAWNBREAKERS_LOG_INFO("EnterWeaponState:EWeaponState_EquipingFromInventory");
	m_bHandled = false;

	ADBCharacter *TCharacter = GetWeaponOwner();
	if (TCharacter)
	{
		TCharacter->PlayAnimMontage(m_EquipAnim, 1.f, NAME_None);
		GetWeapon()->PlayWeaponSound(m_EquipSound);
	}
}

void UDBWeaponStateEquipFromInventory::ExitWeaponState()
{
	DAWNBREAKERS_LOG_INFO("ExitWeaponState:EWeaponState_EquipingFromInventory");
}

bool UDBWeaponStateEquipFromInventory::CanTransferTo(EWeaponState::Type NewState)
{
	if (NewState == EWeaponState::EWeaponState_Inactive  &&
		IsHandled())
	{
		return true;
	}

	return false;
}

void UDBWeaponStateEquipFromInventory::OnEquipAnimFinish()
{

	GetOuterUDBWeaponStateMachine()->GotoState(EWeaponState::EWeaponState_Active);
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
		TOwner->SetHoldWeapon(TWeapon);
		GetOuterUDBWeaponStateMachine()->GotoState(EWeaponState::EWeaponState_Active);
	}
}

