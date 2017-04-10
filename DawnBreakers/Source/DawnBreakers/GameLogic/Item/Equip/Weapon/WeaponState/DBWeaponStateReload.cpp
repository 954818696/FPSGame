// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponStateReload.h"

UDBWeaponStateReload::UDBWeaponStateReload(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	m_ReloadStage(EReloadStage::E_ReloadStage_PullEmptyClip),
	m_AmmoClip(nullptr)
{
	m_StateID = EWeaponState::EWeaponState_Reloading;

}

void UDBWeaponStateReload::EnterWeaponState()
{
	DAWNBREAKERS_LOG_INFO("EnterWeaponState:EWeaponState_Reloading");
	m_bHandled = false;
	ADBCharacter* TCharacter = GetWeaponOwner();
	ADBWeaponBase* TWeapon = GetWeapon();
	if (TCharacter)
	{
		TWeapon->OnWeaponAnimPlayingOnePoint().Clear();
		TWeapon->OnWeaponAnimPlayingOnePoint().AddUObject(this, &UDBWeaponStateReload::PullOrPushClip);

		TWeapon->OnWeaponAnimFinish().Clear();
		TWeapon->OnWeaponAnimFinish().AddUObject(this, &UDBWeaponStateReload::OnReloadAnimFinish);

		TCharacter->PlayAnimMontage(m_ReloadAnim, 1.f, NAME_None);
		TWeapon->PlayWeaponSound(m_ReloadSound);
	}
}

void UDBWeaponStateReload::ExitWeaponState()
{
	DAWNBREAKERS_LOG_INFO("ExitWeaponState:EWeaponState_Reloading");
	m_ReloadStage = EReloadStage::E_ReloadStage_PullEmptyClip;
}

bool UDBWeaponStateReload::CanTransferTo(EWeaponState::Type NewState, UDBWeaponStateBase* State)
{
	if (NewState == EWeaponState::EWeaponState_Unequiping || NewState == EWeaponState::EWeaponState_Inactive)
	{
		return true;
	}
	else if (IsHandled() && NewState == EWeaponState::EWeaponState_Active)
	{
		return true;
	}

	return false;
}

void UDBWeaponStateReload::OnReloadAnimFinish()
{
	m_bHandled = true;
	ADBCharacter* TCharacter = GetWeaponOwner();
	if (TCharacter)
	{
		m_AmmoClip->Destroy();
		GetWeapon()->GetMeshComp()->UnHideBoneByName(FName(TEXT("b_gun_mag")));
		TCharacter->StopAnimMontage(m_ReloadAnim);
		ADBShootWeaponBase* TShootWeapon = Cast<ADBShootWeaponBase>(GetWeapon());
		TShootWeapon->WeaponReloadAmmo();
		GetOuterUDBWeaponStateMachine()->GotoState(EWeaponState::EWeaponState_Active);
	}
}

void UDBWeaponStateReload::PullOrPushClip()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (m_EmptyAmmoClipClass && m_FullAmmoClipClass)
	{
		if (m_ReloadStage == EReloadStage::E_ReloadStage_PullEmptyClip)
		{
			GetWeapon()->GetMeshComp()->HideBoneByName(FName(TEXT("b_gun_mag")), EPhysBodyOp::PBO_None);
			m_ReloadStage = EReloadStage::E_ReloadStage_PushFullClip;
			m_AmmoClip = GetWeapon()->GetWorld()->SpawnActor<AActor>(m_EmptyAmmoClipClass);
			m_AmmoClip->AttachToComponent(GetWeaponOwner()->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("AmmoReload")));
		}
		else if (m_ReloadStage == EReloadStage::E_ReloadStage_PushFullClip)
		{
			m_AmmoClip->Destroy();
			m_AmmoClip = GetWeapon()->GetWorld()->SpawnActor<AActor>(m_FullAmmoClipClass);
			m_AmmoClip->AttachToComponent(GetWeaponOwner()->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("AmmoReload")));
		}
	}
}

