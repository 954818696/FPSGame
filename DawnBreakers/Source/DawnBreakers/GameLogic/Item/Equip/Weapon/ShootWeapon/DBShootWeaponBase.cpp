// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBShootWeaponBase.h"
#include "GameLogic/Item/Equip/Weapon/WeaponState/DBWeaponStateFiring.h"
#include "Runtime/UMG/Public/Components/WidgetComponent.h"


ADBShootWeaponBase::ADBShootWeaponBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	WeaponWidgetComp = ObjectInitializer.CreateDefaultSubobject<UWidgetComponent>(this, TEXT("WeaponShowWidget"));
	WeaponWidgetComp->AttachToComponent(m_SkeletalMeshComp, FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("b_gun_stock")));
	WeaponWidgetComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	FTransform WeaponWidgetTransform;
	WeaponWidgetTransform.SetLocation(FVector(2.3f, -5.f, -1.2f));
	WeaponWidgetTransform.SetRotation(FQuat(-116.f, -90.f, 26.f, 1.f));

	WeaponWidgetTransform.SetScale3D(FVector(0.009f, 0.009f, 0.009f));
	//WeaponWidgetComp->SetRelativeTransform(WeaponWidgetTransform);
	WeaponWidgetComp->RelativeRotation.Pitch = -90.f;
	WeaponWidgetComp->RelativeRotation.Yaw = 26.f;
	WeaponWidgetComp->RelativeRotation.Roll = -116.f;
	WeaponWidgetComp->RelativeLocation.X = 2.3f;
	WeaponWidgetComp->RelativeLocation.Y = -5.f;
	WeaponWidgetComp->RelativeLocation.Z = -1.2f;
	WeaponWidgetComp->RelativeScale3D = FVector(0.009f, 0.009f, 0.009f);
}

void ADBShootWeaponBase::OnEquip(bool bEquipedWeaponFromInventory)
{
	Super::OnEquip(bEquipedWeaponFromInventory);

	OnRefreshAmmoForBP();
}

void ADBShootWeaponBase::OnReload()
{
	if (m_CurAmmosInClip < m_AmmoClipSize)
	{
		UDBWeaponStateFiring* TFiringState = Cast<UDBWeaponStateFiring>(m_WeaponStateMachine->GetState(EWeaponState::EWeaponState_Attack));
		ADBCharacter* TOwner = GetItemOwner();
		if (TFiringState && TOwner)
		{
			bool IsHaveAmmo = TOwner->GetInventory()->IsHaveAmmo(TFiringState->m_CostAmmoType);
			if (IsHaveAmmo)
			{
				m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_Reloading);
			}
		}
	}
}

void ADBShootWeaponBase::OnSwitchMode()
{
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_SwitchMode);
}

void ADBShootWeaponBase::OnStartFire()
{
	ADBCharacter* TOwner = GetItemOwner();
	UDBWeaponStateFiring* TFiringState = Cast<UDBWeaponStateFiring>(m_WeaponStateMachine->GetState(EWeaponState::EWeaponState_Attack));
	if (TOwner && TFiringState)
	{
		if (m_CurAmmosInClip > 0)
		{
			Super::OnStartFire();
		}
		else
		{
			bool IsHaveAmmo = TOwner->GetInventory()->IsHaveAmmo(TFiringState->m_CostAmmoType);
			if (IsHaveAmmo)
			{
				OnReload();
			}
			else
			{
				PlayOutOfAmmoSound();
			}
		}
	}
}

void ADBShootWeaponBase::OnStopFire()
{
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_Active);
}

void ADBShootWeaponBase::SetCurAmmosInClip(int32 AmmoAmount)
{
	m_CurAmmosInClip = AmmoAmount < m_AmmoClipSize ? AmmoAmount : m_AmmoClipSize;
}

void ADBShootWeaponBase::ConsumeAmmo(EAmmoType AmmoType, int32 CostAmount)
{
	if (m_CurAmmosInClip > 0)
	{
		--m_CurAmmosInClip;
		OnRefreshAmmoForBP();
	}
	else
	{
		bool IsHaveAmmo = GetItemOwner()->GetInventory()->IsHaveAmmo(AmmoType);
		if (IsHaveAmmo)
		{
			OnReload();
		}
		else
		{
			OnStopFire();
			PlayOutOfAmmoSound();
		}
	}
}

void ADBShootWeaponBase::WeaponReloadAmmo()
{
	ADBCharacter* TOwner = GetItemOwner();
	UDBWeaponStateFiring* TFiringState = Cast<UDBWeaponStateFiring>(m_WeaponStateMachine->GetState(EWeaponState::EWeaponState_Attack));
	if (TFiringState)
	{
		m_CurAmmosInClip += GetItemOwner()->GetInventory()->GetAmmoForWeapon(TFiringState->m_CostAmmoType, m_AmmoClipSize, m_CurAmmosInClip);
		OnRefreshAmmoForBP();
	}
}

void ADBShootWeaponBase::PlayOutOfAmmoSound()
{
	UDBWeaponStateFiring* TFiringState = Cast<UDBWeaponStateFiring>(m_WeaponStateMachine->GetState(EWeaponState::EWeaponState_Attack));
	if (TFiringState)
	{
		PlayWeaponSound(TFiringState->m_RunOutOfAmmoSound);
	}
}

