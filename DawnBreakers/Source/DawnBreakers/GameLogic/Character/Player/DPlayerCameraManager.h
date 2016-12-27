// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/PlayerCameraManager.h"
#include "DPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API ADPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
	ADPlayerCameraManager(const FObjectInitializer& ObjectInitializer);
	
	virtual void UpdateCamera(float DeltaTime) override;

	float mDefaultFOV;

	float mTargetFOV;
};
