// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameLogic/Character/DBBasePlayerController.h"
#include "DBPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API ADBPlayerController : public ADBBasePlayerController
{
	GENERATED_UCLASS_BODY()
	
	
public:

	virtual void Possess(APawn* ControlledPawn) override;

private:
	//////////////////////////////////////
	// Input Control.
	virtual void SetupInputComponent() override;

	void MoveForward(float Delta);

	void MoveRight(float Delta);
	//////////////////////////////////////

private:
	class ADBCharacter* m_ControlledCharacter;
	
};
