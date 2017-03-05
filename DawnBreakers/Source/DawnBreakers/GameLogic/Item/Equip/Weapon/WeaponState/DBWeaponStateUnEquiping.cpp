// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponStateUnEquiping.h"

UDBWeaponStateUnEquiping::UDBWeaponStateUnEquiping(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_StateID = EWeaponState::EWeaponState_Unequiping;

}

void UDBWeaponStateUnEquiping::EnterWeaponState()
{
	DAWNBREAKERS_LOG_INFO("EnterWeaponState:EWeaponState_Unequiping");
	m_bHandled = false;

	ADBCharacter *TCharacter = GetWeaponOwner();
	ADBWeaponBase* TWeapon = GetWeapon();
	if (TCharacter)
	{
		TWeapon->OnWeaponAnimFinish().Clear();
		TWeapon->OnWeaponAnimFinish().AddUObject(this, &UDBWeaponStateUnEquiping::OnUnEquipAnimFinish);
		TWeapon->PlayWeaponSound(m_UnEquipSound);

		TCharacter->PlayAnimMontage(m_UnEquipAnim, 1.f, NAME_None);
	}
}

void UDBWeaponStateUnEquiping::ExitWeaponState()
{
	DAWNBREAKERS_LOG_INFO("ExitWeaponState:EWeaponState_Unequiping");
}

bool UDBWeaponStateUnEquiping::CanTransferTo(EWeaponState::Type NewState)
{
	if (NewState == EWeaponState::EWeaponState_Active && IsHandled())
	{
		return true;
	}

	return false;
}

void UDBWeaponStateUnEquiping::OnUnEquipAnimFinish()
{
	m_bHandled = true;
	GetOuterUDBWeaponStateMachine()->GotoState(EWeaponState::EWeaponState_Inactive);
	ADBWeaponBase* TWeapon = GetWeapon();
	if (TWeapon)
	{
		ADBCharacter* TOwner = Cast<ADBCharacter>(TWeapon->GetOwner());
		USceneComponent* TParentComp = TOwner->GetMesh();
		if (TParentComp)
		{
			TWeapon->AttachToTarget(EItemAttachToTargetType::AttachToInventory, TParentComp);
		}
		TOwner->SetHoldWeapon(nullptr);
	}
}
