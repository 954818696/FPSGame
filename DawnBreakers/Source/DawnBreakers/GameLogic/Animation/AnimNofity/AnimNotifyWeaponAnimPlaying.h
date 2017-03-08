// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotifyWeaponAnimPlaying.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API UAnimNotifyWeaponAnimPlaying : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotifyWeaponAnimPlaying();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
	
};
