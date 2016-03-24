// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DPlayerCharacter.generated.h"

UCLASS(Abstract)
class DAWNBREAKERS_API ADPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	// Sets default values for this character's properties
	ADPlayerCharacter(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void PostInitializeComponents() override;
	
	virtual void Destroyed() override;

	// ----------操控输入处理
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void MoveForward(float val);
	void MoveRight(float val);

	void OnCrouchToggle();

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

	void OnStartJump();
	void OnStopJump();
	void SetIsJumping(bool NewJumping);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetIsJumping(bool NewJumping);
	UPROPERTY(Transient, Replicated)
	bool mbIsJumping;

	void OnStartTargeting();
	void OnStopTargeting();
	void SetTargeting(bool bNewTargeting);
	UFUNCTION(BlueprintCallable, Category = "Game|Weapon")
	bool IsTargeting() const;
	UFUNCTION(reliable, server, WithValidation)
	void ServerSetTargeting(bool bNewTargeting);
	UPROPERTY(Transient, Replicated)
	bool mbIsTargeting;

	void OnStartFire();
	void OnStopFire();
	void StartWeaponFire();
	void StopWeaponFire();

	void OnNextWeapon();
	void OnPrevWeapon();
	void OnReload();





	// ----------角色动作和动画

	

	virtual float PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None) override;

	virtual void StopAnimMontage(class UAnimMontage* AnimMontage) override;

	void StopAllAnimMontages();

	void test();


};
