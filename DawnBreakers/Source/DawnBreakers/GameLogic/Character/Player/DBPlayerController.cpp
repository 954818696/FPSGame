// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBPlayerController.h"
#include "GameLogic/Character/DBCharacter.h"


ADBPlayerController::ADBPlayerController(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void ADBPlayerController::Possess(APawn* ControlledPawn)
{
	Super::Possess(ControlledPawn);

	m_ControlledCharacter = Cast<ADBCharacter>(ControlledPawn);

}

void ADBPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ADBPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ADBPlayerController::MoveRight);
	InputComponent->BindAxis("Turn", this, &APlayerController::AddYawInput);
	InputComponent->BindAxis("LookUp", this, &APlayerController::AddPitchInput);


	//InputComponent->BindAction("Jump", IE_Pressed, this, &ADPlayerCharacter::OnStartJump);
	//InputComponent->BindAction("Jump", IE_Released, this, &ADPlayerCharacter::OnStopJump);
	//InputComponent->BindAction("CrouchToggle", IE_Released, this, &ADPlayerCharacter::OnCrouchToggle);
	//InputComponent->BindAction("Targeting", IE_Pressed, this, &ADPlayerCharacter::OnStartTargeting);
	//InputComponent->BindAction("Targeting", IE_Released, this, &ADPlayerCharacter::OnStopTargeting);

	InputComponent->BindAction("Fire", IE_Pressed, this, &ADBPlayerController::OnStartFire);
	InputComponent->BindAction("Fire", IE_Released, this, &ADBPlayerController::OnStopFire);
}

void ADBPlayerController::MoveForward(float Delta)
{
	if (Delta != 0.f && m_ControlledCharacter != nullptr)
	{
		m_ControlledCharacter->MoveForward(Delta);
	}
}

void ADBPlayerController::MoveRight(float Delta)
{
	if (Delta != 0.f && m_ControlledCharacter != nullptr)
	{
		m_ControlledCharacter->MoveRight(Delta);
	}
}

void ADBPlayerController::OnStartFire()
{
	if (m_ControlledCharacter != nullptr)
	{
		m_ControlledCharacter->OnStartFire();
	}
}

void ADBPlayerController::OnStopFire()
{
	if (m_ControlledCharacter != nullptr)
	{
		m_ControlledCharacter->OnStopFire();
	}
}
