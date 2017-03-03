// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotifyWeaponAnimFinish.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API UAnimNotifyWeaponAnimFinish : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotifyWeaponAnimFinish();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
	
};
