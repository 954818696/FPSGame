// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DBWeaponStateBase.h"
#include "DBWeaponStateReload.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API UDBWeaponStateReload : public UDBWeaponStateBase
{
	GENERATED_UCLASS_BODY()

	enum EReloadStage
	{
		E_ReloadStage_PullEmptyClip,
		E_ReloadStage_PushFullClip,
	};
	
public:

	virtual void EnterWeaponState() override;

	virtual void ExitWeaponState() override;

	virtual bool CanTransferTo(EWeaponState::Type NewState, UDBWeaponStateBase* State);

private:
	void OnReloadAnimFinish();

	void PullOrPushClip();

public:
	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	UAnimMontage* m_ReloadAnim;

	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	USoundBase* m_ReloadSound;

	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	TSubclassOf<AActor> m_EmptyAmmoClipClass;

	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	TSubclassOf<AActor> m_FullAmmoClipClass;

private:
	EReloadStage m_ReloadStage;

	AActor* m_AmmoClip;
};
