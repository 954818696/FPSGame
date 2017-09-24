// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameLogic/Character/Player/Controller/DBBasePlayerController.h"
#include "DBPlayerController.generated.h"


UENUM()
enum class EPlayerInGameState :uint8 
{
	PrepareForGettingIn,
	SpawnPlayer,
	Playing,
	Death,
	Spectating,
	EndMatch,
};

// Extend Reserve
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

	void ApplyDeferredFireInputs();

	//-- GameMdoe Flow.
	void EnterState(EPlayerInGameState State);

	UFUNCTION(BlueprintCallable, Category = ADBPlayerController)
	void Spawn();

	UFUNCTION(BlueprintCallable, Category = ADBPlayerController)
	void SetCanReceiveInput(bool CanReceive);

protected:
	
	virtual void PlayerTick(float DeltaTime) override;

	//////////////////////////////////////
	// Input Control.
	virtual void SetupInputComponent() override;

	void MoveForward(float Delta);

	void MoveRight(float Delta);

	void CustomAddPitchInput(float Delta);

	void CustomAddYawInput(float Delta);

	void OnStartJump();

	void OnStopJump();

	void OnCrouchToggle();

	void OnStartFire();

	void OnStopFire();

	void OnReload();

	void OnStartTargeting();

	void OnStopTargeting();

	void OnPrevWeapon();

	void OnNextWeapon();

	void OnSwitchCameraMode();

	void OnInteractWithItem();

	void OnDropItem();

	void OnConsultESC();

	//////////////////////////////////////

protected:
	EPlayerInGameState PlayerInGameState;

private:
	class ADBCharacter* m_ControlledCharacter;
	
	// To Support Multikeys press trigger firing.
	TArray< FDeferredFireInput, TInlineAllocator<2> > m_DeferredFireInputs;

	bool m_CanReceiveInput;


};
