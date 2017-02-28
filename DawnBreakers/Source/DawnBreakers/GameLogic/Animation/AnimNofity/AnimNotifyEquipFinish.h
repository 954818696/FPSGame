// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotifyEquipFinish.generated.h"

/**
 * 
 */
UCLASS(const, hidecategories = Object, collapsecategories, meta = (DisplayName = "EquipFinishNotify"))
class DAWNBREAKERS_API UAnimNotifyEquipFinish : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotifyEquipFinish();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
