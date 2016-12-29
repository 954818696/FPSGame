// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DawnBreakers.h"
#include "GameFramework/Actor.h"
#include "WeaponConfig.h"

#include "DShooterWeaponBase.generated.h"




UCLASS(Abstract, Blueprintable)
class DAWNBREAKERS_API ADShooterWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	ADShooterWeaponBase(const FObjectInitializer& ObjectInitializer);

	virtual void PostInitializeComponents() override;

	virtual void Destroyed() override;

	virtual void StartFire();

	virtual void StopFire();

	virtual void StartReload();

	virtual void StopReload();

	virtual void OnEquip();

	virtual void OnEquipFinished();

protected:
	void SetWeaponState(EWeaponState::Type NewWeaponState);

	FORCEINLINE EWeaponState::Type GetWeaponState() const;

private:
	void HandleFire();

	void SimulateWeaponFire();

protected:
	class ADPlayerCharacter* m_OwnedPawn;

	UPROPERTY(EditDefaultsOnly, Category = WeaponConfig)
	FWeaponData m_WeaponConfig;

	/////////////////////////////////////////////////////
	//  Weapon VFX , SFX, Animation, CameraShake.
	/////////////////////////////////////////////////////
	UPROPERTY(EditDefaultsOnly, Category = WeaponConfig)
	FName m_MuzzleAttachPointName;

	UParticleSystemComponent* MuzzlePSC;

	UPROPERTY(EditDefaultsOnly, Category = WeaponConfig)
	UParticleSystem* m_MuzzlePS;

	UAudioComponent* m_FireAC;

	UPROPERTY(EditDefaultsOnly, Category = WeaponConfig)
	USoundCue* m_FireSoundCue;

	UPROPERTY(EditDefaultsOnly, Category = WeaponConfig)
	USoundCue* m_FireLoopSoundCue;
	
	UPROPERTY(EditDefaultsOnly, Category = WeaponConfig)
	USoundCue* m_FireFinishSoundCue;

	UPROPERTY(EditDefaultsOnly, Category = WeaponConfig)
	USoundCue* m_OutOfAmmoSoundCue;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* m_ReloadSoundCue;

	UPROPERTY(EditDefaultsOnly, Category = WeaponConfig)
	TSubclassOf<UCameraShake> m_FireCameraShake;

private:
	EWeaponState::Type m_WeaponState;

	bool m_bPendingReload;

	FTimerHandle TimeHandle_HandleFiring;

};
