// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameLogic/Item/Equip/Inventory/DBInventoryItemBase.h"
#include "WeaponState/DBWeaponStateMachine.h"
#include "DBWeaponConfig.h"
#include "DBWeaponBase.generated.h"




/**
 * 
 */
UCLASS(Abstract)
class DAWNBREAKERS_API ADBWeaponBase : public ADBInventoryItemBase
{
	GENERATED_UCLASS_BODY()

	DECLARE_EVENT(ADBWeaponBase, FWeaponAnimFinishEvent)
	DECLARE_EVENT(ADBWeaponBase, FWeaponAnimPlayingOnePointEvent)

public:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual void OnEquip(bool bEquipedWeaponFromInventory);

	virtual void OnUnEquip();

	// 近战，投掷武器使用激发也是走此
	virtual void OnStartFire();

	virtual void OnStopFire();

	void PlayWeaponSound(USoundBase* SoundToPlay);

	FORCEINLINE int32 GetCurrentFireMode() const { return m_CurrentFireMode;}

	FORCEINLINE bool IsInState(EWeaponState::Type WeaponState) const;

	FORCEINLINE int32 GetWeaponHoldStanceType();

	FORCEINLINE FWeaponAnimFinishEvent& OnWeaponAnimFinish() { return WeaponAnimFinishEvent; }

	FORCEINLINE FWeaponAnimPlayingOnePointEvent& OnWeaponAnimPlayingOnePoint() { return WeaponAnimPlayingOnePointEvent; }

	FORCEINLINE void PlayFireShotEffectByIndex(int32 EffectIndex);

	FORCEINLINE void StopFireShotEffectByIndex(int32 EffectIndex);

	static void SetInstanceOnFireEffectArray(AActor* Weapon, TArray<UParticleSystemComponent*>& OnFireEffectArray);

	/*武器激发特效，不仅仅局限于枪械。近战，投掷均可*/
	UPROPERTY(EditAnywhere, Category = Weapon)
	TArray<UParticleSystemComponent*> FireShotEffect;

protected:
	/** Weapon State Machine */
	UPROPERTY(EditDefaultsOnly, Category = WeaponState, NoClear)
	class UDBWeaponStateMachine* m_WeaponStateMachine;

	/* Plays the idle, wandering or hunting sound */
	UPROPERTY(VisibleAnywhere, Category = Sound)
	UAudioComponent* m_AudioComp;

	UPROPERTY(EditDefaultsOnly, Category = WeaponAnim)
	EWeaponTypeForEquipAnim m_WeaponHoldType;


	// 和tarry中firestate顺序对应
	int32 m_CurrentFireMode;

private:
	FWeaponAnimFinishEvent	WeaponAnimFinishEvent;
	FWeaponAnimPlayingOnePointEvent WeaponAnimPlayingOnePointEvent;
};
