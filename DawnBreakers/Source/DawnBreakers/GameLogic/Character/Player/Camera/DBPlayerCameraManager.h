// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/PlayerCameraManager.h"
#include "DBPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API ADBPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_UCLASS_BODY()

public:
	virtual void UpdateCamera(float DeltaTime) override;
	
	
private:
	float m_DefaultFOV;
	float m_TargetFOV;
};
