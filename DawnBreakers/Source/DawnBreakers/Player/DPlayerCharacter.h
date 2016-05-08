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

	// 基本移动
	void MoveForward(float val);
	void MoveRight(float val);

	// 蹲
	void OnCrouchToggle();

	// 疾跑
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

	// 跳跃处理
	void OnStartJump();
	void OnStopJump();
	void SetIsJumping(bool NewJumping);
	UFUNCTION(BlueprintCallable, Category = Pawn)
	bool IsInitJumping() const;
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetIsJumping(bool NewJumping);
	UPROPERTY(Transient, Replicated)
	bool mbIsJumping;

	// 近瞄处理
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

	// 开火处理
	void OnStartFire();
	void OnStopFire();
	void StartWeaponFire();
	void StopWeaponFire();
	UFUNCTION(BlueprintCallable, Category = "Game|Weapon")
	FRotator GetAimOffsets() const;

	void OnNextWeapon();
	void OnPrevWeapon();
	void OnReload();


	// 角色动作和动画
	virtual float PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None) override;
	virtual void StopAnimMontage(class UAnimMontage* AnimMontage) override;
	void StopAllAnimMontages();
	void test();

	// 武器挂载
	FName GetWeaponAttachPoint() const;

private:

	// 视角相机
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	UCameraComponent * mCameraFP;
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	UCameraComponent * mCameraTP;
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	USpringArmComponent * mCameraBoomComp;

	// 第一人称视角模型
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* mMeshFP;
};
