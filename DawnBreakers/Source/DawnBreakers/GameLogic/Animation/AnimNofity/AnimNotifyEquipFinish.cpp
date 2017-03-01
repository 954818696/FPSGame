// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "AnimNotifyEquipFinish.h"
#include "GameLogic/Item/Equip/Weapon/DBWeaponBase.h"




UAnimNotifyEquipFinish::UAnimNotifyEquipFinish()
{

}

void UAnimNotifyEquipFinish::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	DAWNBREAKERS_LOG_INFO("UAnimNotifyEquipFinish::Notify");
	
	UAnimInstance* TAnimInstance = MeshComp->GetAnimInstance();
	if (TAnimInstance && TAnimInstance->IsValidLowLevel())
	{
		UDBCharacterAnimInstance* TDBCharacterAnimInstance = Cast<UDBCharacterAnimInstance>(TAnimInstance);
		if (TDBCharacterAnimInstance && TDBCharacterAnimInstance->IsValidLowLevel())
		{
			ADBCharacter* TDBCharacter = TDBCharacterAnimInstance->GetCharacter();
			if (TDBCharacter)
			{
				TDBCharacter->GetHoldWeapon()->OnEquipAnimFinish().Broadcast();
			}
		}
	}
}
