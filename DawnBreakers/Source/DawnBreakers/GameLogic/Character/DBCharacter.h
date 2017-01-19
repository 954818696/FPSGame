// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "DBCharacter.generated.h"

UCLASS()
class DAWNBREAKERS_API ADBCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

	enum ECameraMode
	{
		E_FirstPersonPerspective    = 1,
		E_ThirdPersonPerspective  = 2,
	};

public:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	//////////////////////////////////////
	// Motion and Controll
	void MoveForward(float Delta);

	void MoveRight(float Delta);

	void OnStartJump();

	void OnStopJump();

	void OnStartFire();

	void OnStopFire();

	void OnStartTargeting();

	void OnStopTargeting();

	void SwitchEquipWeapon(bool bNext);

	void SwitchCamaraMode();
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

	void SetFPSCamera();
	
	//////////////////////////////////////

	//////////////////////////////////////

private:
	class ADBWeaponBase* m_Weapon;

	//////////////////////////////////////
	// Camera.
	UCameraComponent * m_CameraComp;

	UPROPERTY(EditDefaultsOnly, Category = "DBCamera")
	USpringArmComponent * m_CameraBoomComp;

	UPROPERTY(EditDefaultsOnly, Category = "DBCamera")
	FTransform m_FPSCameraPos;

	ECameraMode m_CurCameraMode;
	//////////////////////////////////////
	
};
