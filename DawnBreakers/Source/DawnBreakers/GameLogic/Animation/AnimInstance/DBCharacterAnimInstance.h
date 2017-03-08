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
	GENERATED_UCLASS_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTime) override;

	FORCEINLINE void SetWeaponHoldStance(int32 HoldType) {	m_WeaponHoldStance = HoldType; }

	FORCEINLINE class ADBCharacter* GetCharacter() const;

protected:
	// 不用EWeaponTypeForEquipAnim,减少编译时间
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UDBCharacterAnimInstance)
	int32 m_WeaponHoldStance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UDBCharacterAnimInstance)
	FRotator m_ArmsRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UDBCharacterAnimInstance)
	float m_ViewPitch;

	UPROPERTY(BlueprintReadOnly, Category = UDBCharacterAnimInstance)
	ADBCharacter * m_CharacterOwner;
};
