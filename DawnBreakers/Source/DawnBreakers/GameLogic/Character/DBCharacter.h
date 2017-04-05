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

	void AddYawInput(float Delta);

	void AddPitchInput(float Delta);

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

	//////////////////////////////////////
	// Camera.
	//void CalcCamera(float DeltaTime, FMinimalViewInfo & OutResult) override;

	FVector GetFiringDirection();

	void UpdateIronSightLoc(ADBWeaponBase* NewShootWeapon);

	void SwitchCamaraMode();

	void SetCameraAim(float Delta, bool bAim);

	FORCEINLINE bool IsTargeting() const { return m_IsTargeting; }

	FORCEINLINE void PlayCameraShake(TSubclassOf<class UCameraShake> Shake, float Scale = 1.f, ECameraAnimPlaySpace::Type PlaySpace = ECameraAnimPlaySpace::CameraLocal, FRotator UserPlaySpaceRot = FRotator::ZeroRotator);
	//////////////////////////////////////

	//////////////////////////////////////
	// Born Default Data Initializing.
	void CreateInventory();

	FORCEINLINE class ADBInventoryBase* GetInventory() { return m_Inventory;  }

	//////////////////////////////////////

	FORCEINLINE void SetHoldWeapon(ADBWeaponBase* NewWeapon) { m_HoldWeapon = NewWeapon; }

	FORCEINLINE ADBWeaponBase* GetHoldWeapon() { return m_HoldWeapon; }

	FORCEINLINE float ADBCharacter::GetViewPitch() const;

	FORCEINLINE void GetArmRotation(FRotator & OutRotation) const;

	class UDBCharacterAnimInstance* GetAnimInstance();

private:
	void InteractQueryTick();

	AActor* QueryItemByRay();

	void SetFPSCamera();

	void PutHandWeaponToInventory();

	void EquipPendedWeapon();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ADBCharacter)
	class UDBCharacterMovementComponent* m_CharacterMovement;

	UPROPERTY(EditDefaultsOnly , Category = ADBCharacter)
	TSubclassOf<ADBInventoryBase> m_InventoryClass;

	UPROPERTY(EditDefaultsOnly, Category = ADBCharacter)
	float m_MaxInteractableDistance;

private:
	ADBInventoryBase* m_Inventory;

	ADBWeaponBase* m_HoldWeapon;

	ADBWeaponBase* m_PendEquipWeapon;
	bool m_bPendEquipFromInventory;

	AActor* m_FocusedInteractItem;

	FTimerHandle TimerHandle_PendWeaponEquip;

	//////////////////////////////////////
	// Camera.
	UPROPERTY(EditAnywhere, Category = "DBCamera")
	UCameraComponent * m_CameraComp;

	UPROPERTY(EditDefaultsOnly, Category = "DBCamera")
	USpringArmComponent * m_CameraBoomComp;

	ECameraMode m_CurCameraMode;

	FVector m_IronSightLoc;

	bool m_IsTargeting;
	//////////////////////////////////////

	//////////////////////////////////////
	// Animation.
	class UDBCharacterAnimInstance* m_AnimationInstance;

	FRotator m_ArmsLagRotation;

	float m_PrevViewPitchRotation;

	float m_PrevViewYawRotation;
	//////////////////////////////////////
};
