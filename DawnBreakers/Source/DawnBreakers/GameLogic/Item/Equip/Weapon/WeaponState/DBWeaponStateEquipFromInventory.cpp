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
	//if (!EquipAnimFinishHandle.IsValid())
	//{
		//EquipAnimFinishHandle = GetWeapon()->OnWeaponAnimFinish().AddUObject(this, &UDBWeaponStateEquipFromInventory::OnEquipAnimFinish);
	//}
}

void UDBWeaponStateEquipFromInventory::EnterWeaponState()
{
	DAWNBREAKERS_LOG_INFO("EnterWeaponState:EWeaponState_EquipingFromInventory %s", *GetWeapon()->GetName());
	m_bHandled = false;

	ADBCharacter *TCharacter = GetWeaponOwner();
	ADBWeaponBase* TWeapon = GetWeapon();
	if (TCharacter && TWeapon)
	{
		TCharacter->SetHoldWeapon(TWeapon);


		TWeapon->OnWeaponAnimFinish().Clear();
		TWeapon->OnWeaponAnimFinish().AddUObject(this, &UDBWeaponStateEquipFromInventory::OnEquipAnimFinish);
		TWeapon->OnWeaponAnimPlayingOnePoint().Clear();
		TWeapon->OnWeaponAnimPlayingOnePoint().AddUObject(this, &UDBWeaponStateEquipFromInventory::OnAttachWeaponToHand);

		TCharacter->PlayAnimMontage(m_EquipAnim, 1.f, NAME_None);
		TWeapon->PlayWeaponSound(m_EquipSound);
	}
}

void UDBWeaponStateEquipFromInventory::ExitWeaponState()
{
	DAWNBREAKERS_LOG_INFO("ExitWeaponState:EWeaponState_EquipingFromInventory %s", *GetWeapon()->GetName());
}

bool UDBWeaponStateEquipFromInventory::CanTransferTo(EWeaponState::Type NewState, UDBWeaponStateBase* State)
{
	if (NewState == EWeaponState::EWeaponState_Active  &&
		IsHandled())
	{
		return true;
	}

	return false;
}

void UDBWeaponStateEquipFromInventory::OnEquipAnimFinish()
{
	m_bHandled = true;
	ADBCharacter *TCharacter = GetWeaponOwner();
	if (TCharacter)
	{
		TCharacter->UpdateIronSightLoc(GetWeapon());
	}
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_Active);
}

void UDBWeaponStateEquipFromInventory::OnAttachWeaponToHand()
{
	ADBCharacter *TCharacter = GetWeaponOwner();
	ADBWeaponBase* TWeapon = GetWeapon();
	if (TCharacter && TWeapon)
	{
		USceneComponent* TParentComp = TCharacter->GetMesh();
		if (TParentComp)
		{
			TWeapon->AttachToTarget(EItemAttachToTargetType::AttachToCharacter, TParentComp);
		}
		UDBCharacterAnimInstance* TAnimInstance = TCharacter->GetAnimInstance();
		TAnimInstance->SetWeaponHoldStance(TWeapon->GetWeaponHoldStanceType());
	}
}

