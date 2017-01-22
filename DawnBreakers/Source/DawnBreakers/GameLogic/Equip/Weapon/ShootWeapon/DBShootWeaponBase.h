// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameLogic/Equip/Weapon/DBWeaponBase.h"
#include "DBShootWeaponBase.generated.h"

/**
 * 
 */
UCLASS(Placeable)
class DAWNBREAKERS_API ADBShootWeaponBase : public ADBWeaponBase
{
	GENERATED_UCLASS_BODY()
	
public:
	void OnStartFire();

	void OnStopFire();

	FORCEINLINE int32 GetCurrentFireMode() const
	{
		return m_CurrentFireMode;
	}

	virtual void SetInteractFocus() override;

	virtual void LoseInteractFocus() override;
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "ADBInventoryItemBase")
	UBoxComponent* m_FakeSkeletalMeshPhysicBoxComp;

	UPROPERTY(VisibleAnywhere, Category = "ADBInventoryItemBase")
	USkeletalMeshComponent* m_SkeletalMeshComp;

	

	/** Weapon State Machine */
	UPROPERTY(EditDefaultsOnly, Category = WeaponState, NoClear)
	class UDBWeaponStateMachine* m_WeaponStateMachine;

	int32 m_CurrentFireMode;
};
