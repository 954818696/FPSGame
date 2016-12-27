// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameLogic/Character/DBBasePlayerController.h"
#include "DBPlayerController.generated.h"


struct FDeferredFireInput
{
	bool bStartFire;

	FDeferredFireInput(uint8 InFireMode, bool bInStartFire)
		: bStartFire(bInStartFire)
	{

	}
};

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

	void OnStartFire();

	void OnStopFire();
	//////////////////////////////////////

private:
	class ADBCharacter* m_ControlledCharacter;
	
	TArray< FDeferredFireInput, TInlineAllocator<2> > m_DeferredFireInputs;
};
