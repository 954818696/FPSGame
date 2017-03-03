// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "AnimNotifyWeaponAnimFinish.h"

UAnimNotifyWeaponAnimFinish::UAnimNotifyWeaponAnimFinish()
{

}

void UAnimNotifyWeaponAnimFinish::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	DAWNBREAKERS_LOG_INFO("UAnimNotifyWeaponAnimFinish::Notify");

	UAnimInstance* TAnimInstance = MeshComp->GetAnimInstance();
	if (TAnimInstance && TAnimInstance->IsValidLowLevel())
	{
		UDBCharacterAnimInstance* TDBCharacterAnimInstance = Cast<UDBCharacterAnimInstance>(TAnimInstance);
		if (TDBCharacterAnimInstance && TDBCharacterAnimInstance->IsValidLowLevel())
		{
			ADBCharacter* TDBCharacter = TDBCharacterAnimInstance->GetCharacter();
			if (TDBCharacter)
			{
				TDBCharacter->GetHoldWeapon()->OnWeaponAnimFinish().Broadcast();
			}
		}
	}
}
