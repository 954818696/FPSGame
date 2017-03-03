// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "DBCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API UDBCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	FORCEINLINE void SetWeaponHoldStance(int32 HoldType) {	m_WeaponHoldStance = HoldType; }

	class ADBCharacter* GetCharacter() const;

protected:
	// ����EWeaponTypeForEquipAnim,���ٱ���ʱ��
	UPROPERTY(BlueprintReadOnly, Category = UDBCharacterAnimInstance)
	int32 m_WeaponHoldStance;
	
};
