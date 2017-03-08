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
	DAWNBREAKERS_LOG_INFO("EnterWeaponState:EWeaponState_Unequiping %s", *GetWeapon()->GetName());
	m_bHandled = false;

	ADBCharacter *TCharacter = GetWeaponOwner();
	ADBWeaponBase* TWeapon = GetWeapon();
	if (TCharacter)
	{
		UDBCharacterAnimInstance* TAnimInstance = TCharacter->GetAnimInstance();
		TAnimInstance->SetWeaponHoldStance(0);

		TWeapon->OnWeaponAnimFinish().Clear();
		TWeapon->OnWeaponAnimFinish().AddUObject(this, &UDBWeaponStateUnEquiping::OnUnEquipAnimFinish);
		TWeapon->OnWeaponAnimPlayingOnePoint().Clear();
		TWeapon->OnWeaponAnimPlayingOnePoint().AddUObject(this, &UDBWeaponStateUnEquiping::OnAttachWeaponToInventory);

		TWeapon->PlayWeaponSound(m_UnEquipSound);
		TCharacter->PlayAnimMontage(m_UnEquipAnim, 1.f, NAME_None);
	}
}

void UDBWeaponStateUnEquiping::ExitWeaponState()
{
	DAWNBREAKERS_LOG_INFO("ExitWeaponState:EWeaponState_Unequiping %s", *GetWeapon()->GetName());
}

bool UDBWeaponStateUnEquiping::CanTransferTo(EWeaponState::Type NewState)
{
	if (NewState == EWeaponState::EWeaponState_Inactive && IsHandled())
	{
		return true;
	}

	return false;
}

void UDBWeaponStateUnEquiping::OnUnEquipAnimFinish()
{
	m_bHandled = true;
	GetOuterUDBWeaponStateMachine()->GotoState(EWeaponState::EWeaponState_Inactive);
	ADBCharacter *TCharacter = GetWeaponOwner();
	if (TCharacter)
	{
		TCharacter->SetHoldWeapon(nullptr);
	}
}

void UDBWeaponStateUnEquiping::OnAttachWeaponToInventory()
{
	ADBWeaponBase* TWeapon = GetWeapon();
	if (TWeapon)
	{
		ADBCharacter* TOwner = Cast<ADBCharacter>(TWeapon->GetOwner());
		USceneComponent* TParentComp = TOwner->GetMesh();
		if (TParentComp)
		{
			TWeapon->AttachToTarget(EItemAttachToTargetType::AttachToInventory, TParentComp);
		}
	}
}
