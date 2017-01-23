// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameLogic/Equip/Weapon/DBWeaponBase.h"
#include "DBShootWeaponBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, Placeable)
class DAWNBREAKERS_API ADBShootWeaponBase : public ADBWeaponBase
{
	GENERATED_UCLASS_BODY()
	
public:

	virtual void SetInteractFocus() override;

	virtual void LoseInteractFocus() override;
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "ADBInventoryItemBase")
	UBoxComponent* m_FakeSkeletalMeshPhysicBoxComp;

	UPROPERTY(VisibleAnywhere, Category = "ADBInventoryItemBase")
	USkeletalMeshComponent* m_SkeletalMeshComp;


};
