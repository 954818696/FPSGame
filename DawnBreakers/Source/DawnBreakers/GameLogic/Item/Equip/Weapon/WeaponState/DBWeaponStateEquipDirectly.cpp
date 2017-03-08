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
	//if (!EquipDirectlyAnimFinishHandle.IsValid())
	//{
	//	EquipDirectlyAnimFinishHandle = GetWeapon()->OnWeaponAnimFinish().AddUObject(this, &UDBWeaponStateEquipDirectly::OnEquipDirectlyAnimFinish);
	//}
}

void UDBWeaponStateEquipDirectly::EnterWeaponState()
{
	DAWNBREAKERS_LOG_INFO("EnterWeaponState:EWeaponState_EquipingDirectly %s", *GetWeapon()->GetName());
	m_bHandled = false;

	ADBCharacter *TCharacter = GetWeaponOwner();
	ADBWeaponBase* TWeapon = GetWeapon();
	if (TCharacter && TWeapon)
	{
		UDBCharacterAnimInstance* TAnimInstance = TCharacter->GetAnimInstance();
		TAnimInstance->SetWeaponHoldStance(TWeapon->GetWeaponHoldStanceType());
		TCharacter->SetHoldWeapon(TWeapon);

		TWeapon->OnWeaponAnimFinish().Clear();
		TWeapon->OnWeaponAnimFinish().AddUObject(this, &UDBWeaponStateEquipDirectly::OnEquipDirectlyAnimFinish);

		USceneComponent* TParentComp = TCharacter->GetMesh();
		if (TParentComp)
		{
			TWeapon->AttachToTarget(EItemAttachToTargetType::AttachToCharacter, TParentComp);
		}
		TCharacter->PlayAnimMontage(m_EquipDirectlyAnim, 1.f, NAME_None);
		TWeapon->PlayWeaponSound(m_EquipDirectlySound);
	}
}

void UDBWeaponStateEquipDirectly::ExitWeaponState()
{
	DAWNBREAKERS_LOG_INFO("ExitWeaponState:EWeaponState_EquipingDirectly %s", *GetWeapon()->GetName());
}

bool UDBWeaponStateEquipDirectly::IsHandled()
{
	return true;
}

bool UDBWeaponStateEquipDirectly::CanTransferTo(EWeaponState::Type NewState)
{
	if (NewState == EWeaponState::EWeaponState_Active  &&
		IsHandled())
	{
		return true;
	}

	return false;
}

void UDBWeaponStateEquipDirectly::OnEquipDirectlyAnimFinish()
{
	m_bHandled = true;
	GetOuterUDBWeaponStateMachine()->GotoState(EWeaponState::EWeaponState_Active);
}

