// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "DBBasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API ADBBasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void SetupInputComponent() override;
	
	
};
