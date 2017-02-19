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
	// Motion and Control
	void MoveForward(float Delta);

	void MoveRight(float Delta);

	void OnStartJump();

	void OnStopJump();

	void OnStartFire();

	void OnStopFire();

	void OnStartTargeting();

	void OnStopTargeting();

	void InteractWithItem();

	void OnPickUpItem(class ADBInventoryItemBase* NewItem);

	void EquipHandWeapon(class ADBWeaponBase* NewWeapon, bool bEquipedWeaponFromInventory);



	void SwitchEquipHandWeapon(bool bNext);

	void SwitchCamaraMode();
	//////////////////////////////////////

	//////////////////////////////////////
	// Born Default Data Initializing.
	void CreateInventory();

	//////////////////////////////////////
private:
	void InteractQueryTick();

	AActor* QueryItemByRay();

	void SetTargeting(bool bNewTargeting);

	void SetFPSCamera();

	void PutHandWeaponToInventory();

	void EquipPendedWeapon();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ADBCharacter)
	class UDBCharacterMovementComponent* m_CharacterMovement;

	UPROPERTY(EditDefaultsOnly , Category = ADBCharacter)
	TSubclassOf<class ADBInventoryBase> m_InventoryClass;

	UPROPERTY(EditDefaultsOnly, Category = ADBCharacter)
	float m_MaxInteractableDistance;

private:
	ADBInventoryBase* m_Inventory;

	ADBWeaponBase* m_HoldWeapon;

	ADBWeaponBase* m_PendEquipWeapon;

	AActor* m_FocusedInteractItem;

	FTimerHandle TimerHandle_PendWeaponEquip;

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
