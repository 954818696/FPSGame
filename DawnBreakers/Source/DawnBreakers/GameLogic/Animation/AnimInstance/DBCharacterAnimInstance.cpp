// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBCharacterAnimInstance.h"
#include "GameLogic/Character/DBCharacter.h"

UDBCharacterAnimInstance::UDBCharacterAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	m_WeaponHoldStance(0)
{

}

void UDBCharacterAnimInstance::NativeInitializeAnimation()
{
	m_CharacterOwner = Cast<ADBCharacter>(GetOwningActor());
}

void UDBCharacterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	if (m_CharacterOwner != nullptr)
	{
		m_CharacterOwner->GetArmRotation(m_ArmsRotation);
		m_ViewPitch = FMath::ClampAngle(m_CharacterOwner->GetViewPitch(), -90.f, 90.f);
	}
}

ADBCharacter* UDBCharacterAnimInstance::GetCharacter() const
{
	if (!m_CharacterOwner)
	{
		return nullptr;
	}

	return m_CharacterOwner;
}