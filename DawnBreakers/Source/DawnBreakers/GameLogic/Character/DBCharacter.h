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

	void SwitchEquipWeapon(bool bNext);
	//////////////////////////////////////

	//////////////////////////////////////
	// Born Default Data Initializing.
	void InitDefaultInventory();

	//////////////////////////////////////

protected:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly)
	class UDBCharacterMovementComponent* m_CharacterMovement;

	UPROPERTY(BlueprintReadOnly, Category = Inventory)
	class ADBInventory* m_Inventory;

private:
	void SetTargeting(bool bNewTargeting);

	void SetDefaultEquipWeapon();
	
	//////////////////////////////////////

	//////////////////////////////////////

private:
	class ADBWeaponBase* m_Weapon;


	
};
