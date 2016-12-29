// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "DBCharacter.generated.h"

UCLASS()
class DAWNBREAKERS_API ADBCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

public:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	//////////////////////////////////////
	// Motion.
	void MoveForward(float Delta);

	void MoveRight(float Delta);

	void OnStartJump();

	void OnStopJump();

	void OnStartFire();

	void OnStopFire();

	void OnStartTargeting();

	void OnStopTargeting();
	//////////////////////////////////////

protected:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly)
	class UDBCharacterMovementComponent* m_CharacterMovement;

private:
	void SetTargeting(bool bNewTargeting);
	
	//////////////////////////////////////

	//////////////////////////////////////

private:
	class ADBWeaponBase* m_Weapon;
	
};
