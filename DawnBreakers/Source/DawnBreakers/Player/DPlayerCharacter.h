// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DPlayerCharacter.generated.h"

#define  DEBUG_FIRE

UCLASS(Abstract)
class DAWNBREAKERS_API ADPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	ADPlayerCharacter(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	virtual void PostInitializeComponents() override;
	virtual void Destroyed() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

public:

	// �����ƶ�
	void MoveForward(float val);
	void MoveRight(float val);

	// ��
	void OnCrouchToggle();

	// ����
	void OnStartRunning();
	void OnStopRunning();
	void UpdateRunSounds(bool bNewRunning); // markabc
	void SetRunning(bool bNewRunning);
	UFUNCTION(reliable, server, WithValidation)
	void ServerSetRunning(bool bNewRunning);
	UFUNCTION(BlueprintCallable, Category = Pawn)
	bool IsRunning() const;
	UPROPERTY(Transient, Replicated)
	bool mbWantsToRun;
	UFUNCTION(BlueprintCallable, Category = Pawn)
	float GetRunningSpeedModifier() const;
	UPROPERTY(EditDefaultsOnly, Category = Pawn)
	float mfRunningSpeedModifier;

	// ��Ծ����
	void OnStartJump();
	void OnStopJump();
	void SetIsJumping(bool NewJumping);
	UFUNCTION(BlueprintCallable, Category = Pawn)
	bool IsInitJumping() const;
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetIsJumping(bool NewJumping);
	UPROPERTY(Transient, Replicated)
	bool mbIsJumping;

	// ���鴦��
	void OnStartTargeting();
	void OnStopTargeting();
	void SetTargeting(bool bNewTargeting);
	UFUNCTION(BlueprintCallable, Category = "Game|Weapon")
	float GetTargetingSpeedModifier() const;
	UPROPERTY(EditDefaultsOnly, Category = "Game|Weapon")
	float mfTargetingSpeedModifier;
	UFUNCTION(BlueprintCallable, Category = "Game|Weapon")
	bool IsTargeting() const;
	UFUNCTION(reliable, server, WithValidation)
	void ServerSetTargeting(bool bNewTargeting);
	UPROPERTY(Transient, Replicated)
	bool mbIsTargeting;

	// ������
	void OnStartFire();
	void OnStopFire();
	void StartWeaponFire();
	void StopWeaponFire();
	UFUNCTION(BlueprintCallable, Category = "Game|Weapon")
	FRotator GetAimOffsets() const;

	void OnNextWeapon();
	void OnPrevWeapon();
	void OnReload();


	// ��ɫ�����Ͷ���
	virtual float PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None) override;
	virtual void StopAnimMontage(class UAnimMontage* AnimMontage) override;
	void StopAllAnimMontages();
	void test();

	// ��������
	FName GetWeaponAttachPoint() const;

private:

	// �ӽ����
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	UCameraComponent * mCameraFP;
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	UCameraComponent * mCameraTP;
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	USpringArmComponent * mCameraBoomComp;

	// ��һ�˳��ӽ�ģ��
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* mMeshFP;
};
