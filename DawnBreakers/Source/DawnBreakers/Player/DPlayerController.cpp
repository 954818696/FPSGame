// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DPlayerController.h"
#include "DPlayerCameraManager.h"

ADPlayerController::ADPlayerController(const FObjectInitializer & ObjectInitializer)
	:Super(ObjectInitializer)
{
	PlayerCameraManagerClass = ADPlayerCameraManager::StaticClass();
}
