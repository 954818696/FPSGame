// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameLogic/Character/DBBasePlayerController.h"
#include "DBPlayerController.generated.h"


struct FDeferredFireInput
{
	bool bStartFire;

	FDeferredFireInput(bool bFire)
		: bStartFire(bFire)
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

	virtual void SetPawn(APawn* InPawn);

	virtual void Possess(APawn* ControlledPawn) override;

	virtual void UnPossess() override;

private:
	
	virtual void PlayerTick(float DeltaTime) override;

	void ApplyDeferredInputs();

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
	
	// To Support Multikey press trigger firing.
	TArray< FDeferredFireInput, TInlineAllocator<2> > m_DeferredFireInputs;
};
