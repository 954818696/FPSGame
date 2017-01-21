// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBPlayerController.h"
#include "GameLogic/Character/DBCharacter.h"


ADBPlayerController::ADBPlayerController(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//PlayerCameraManagerClass = ADPlayerCameraManager::StaticClass();
}

void ADBPlayerController::SetPawn(APawn* InPawn)
{
	AController::SetPawn(InPawn);

}

void ADBPlayerController::Possess(APawn* ControlledPawn)
{
	Super::Possess(ControlledPawn);

	m_ControlledCharacter = Cast<ADBCharacter>(ControlledPawn);

}

void ADBPlayerController::UnPossess()
{
	Super::UnPossess();

	m_ControlledCharacter = nullptr;
}

void ADBPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (m_ControlledCharacter != nullptr)
	{
		ApplyDeferredInputs();
	}
}

void ADBPlayerController::ApplyDeferredInputs()
{
	if (m_ControlledCharacter == nullptr)
	{
		return;
	}

	for (FDeferredFireInput& Input : m_DeferredFireInputs)
	{
		if (Input.bStartFire)
		{
			m_ControlledCharacter->OnStartFire();
		}
		else
		{
			m_ControlledCharacter->OnStopFire();
		}
	}

	m_DeferredFireInputs.Empty();
}

void ADBPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ADBPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ADBPlayerController::MoveRight);
	InputComponent->BindAxis("Turn", this, &APlayerController::AddYawInput);
	InputComponent->BindAxis("LookUp", this, &APlayerController::AddPitchInput);


	InputComponent->BindAction("Jump", IE_Pressed, this, &ADBPlayerController::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &ADBPlayerController::OnStopJump);
	InputComponent->BindAction("CrouchToggle", IE_Released, this, &ADBPlayerController::OnCrouchToggle);
	
	InputComponent->BindAction("Targeting", IE_Pressed, this, &ADBPlayerController::OnStartTargeting);
	InputComponent->BindAction("Targeting", IE_Released, this, &ADBPlayerController::OnStopTargeting);

	InputComponent->BindAction("Fire", IE_Pressed, this, &ADBPlayerController::OnStartFire);
	InputComponent->BindAction("Fire", IE_Released, this, &ADBPlayerController::OnStopFire);

	InputComponent->BindAction("PrevWeapon", IE_Pressed, this, &ADBPlayerController::OnPrevWeapon);
	InputComponent->BindAction("NextWeapon", IE_Pressed, this, &ADBPlayerController::OnNextWeapon);

	InputComponent->BindAction("SwitchCameraMode", IE_Pressed, this, &ADBPlayerController::OnSwitchCameraMode);
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

void ADBPlayerController::OnStartJump()
{

}

void ADBPlayerController::OnStopJump()
{

}

void ADBPlayerController::OnCrouchToggle()
{

}

void ADBPlayerController::OnStartFire()
{
	if (m_ControlledCharacter != nullptr)
	{
		new(m_DeferredFireInputs)FDeferredFireInput(true);
	}
}

void ADBPlayerController::OnStopFire()
{
	if (m_ControlledCharacter != nullptr)
	{
		new(m_DeferredFireInputs)FDeferredFireInput(false);
	}
}

void ADBPlayerController::OnStartTargeting()
{
	if (m_ControlledCharacter != nullptr)
	{
		m_ControlledCharacter->OnStartTargeting();
	}
}

void ADBPlayerController::OnStopTargeting()
{
	if (m_ControlledCharacter != nullptr)
	{
		m_ControlledCharacter->OnStopTargeting();
	}
}

void ADBPlayerController::OnPrevWeapon()
{
	if (m_ControlledCharacter)
	{
		m_ControlledCharacter->SwitchEquipHandWeapon(false);
	}
}

void ADBPlayerController::OnNextWeapon()
{
	if (m_ControlledCharacter)
	{
		m_ControlledCharacter->SwitchEquipHandWeapon(true);
	}
}

void ADBPlayerController::OnSwitchCameraMode()
{
	if (m_ControlledCharacter)
	{
		m_ControlledCharacter->SwitchCamaraMode();
	}
}
