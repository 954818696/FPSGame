// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponStateEquipDirectly.h"


UDBWeaponStateEquipDirectly::UDBWeaponStateEquipDirectly(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_StateID = EWeaponState::EWeaponState_EquipingDirectly;
}

void UDBWeaponStateEquipDirectly::EnterWeaponState()
{
	DAWNBREAKERS_LOG_INFO("EnterWeaponState:EWeaponState_EquipingDirectly");
	ADBWeaponBase* TWeapon = GetWeapon();
	if (TWeapon)
	{
		ADBCharacter* TOwner = Cast<ADBCharacter>(TWeapon->GetOwner());
		USceneComponent* TParentComp = TOwner->GetMesh();
		if (TParentComp)
		{
			TWeapon->AttachToTarget(EItemAttachToTargetType::AttachToCharacter, TParentComp);
		}
	}
	GetOuterUDBWeaponStateMachine()->GotoState(EWeaponState::EWeaponState_Active);
}

void UDBWeaponStateEquipDirectly::ExitWeaponState()
{
	DAWNBREAKERS_LOG_INFO("ExitWeaponState:EWeaponState_EquipingDirectly");
}

bool UDBWeaponStateEquipDirectly::IsHandled()
{
	return true;
}

