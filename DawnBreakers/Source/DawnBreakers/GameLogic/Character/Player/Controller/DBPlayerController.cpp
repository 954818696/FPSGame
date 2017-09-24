// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBPlayerController.h"
#include "GameLogic/Character/Player/DBCharacter.h"
#include "GameModule/Event/EventSets.h"
#include "GameLogic/GameRules/GameMode/DBBattleGameModeBase.h"

ADBPlayerController::ADBPlayerController(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	m_CanReceiveInput(true)
{
	PlayerCameraManagerClass = ADBPlayerCameraManager::StaticClass();
}

void ADBPlayerController::SetPawn(APawn* InPawn)
{
	AController::SetPawn(InPawn);

	m_ControlledCharacter = Cast<ADBCharacter>(InPawn);

}

void ADBPlayerController::Possess(APawn* ControlledPawn)
{
	Super::Possess(ControlledPawn);



}

void ADBPlayerController::UnPossess()
{
	Super::UnPossess();

	m_ControlledCharacter = nullptr;
}

void ADBPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

}



void ADBPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ADBPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ADBPlayerController::MoveRight);
	InputComponent->BindAxis("Turn", this, &ADBPlayerController::CustomAddYawInput);
	InputComponent->BindAxis("LookUp", this, &ADBPlayerController::CustomAddPitchInput);

	
	InputComponent->BindAction("Jump", IE_Pressed, this, &ADBPlayerController::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &ADBPlayerController::OnStopJump);
	InputComponent->BindAction("CrouchToggle", IE_Released, this, &ADBPlayerController::OnCrouchToggle);
	
	InputComponent->BindAction("Targeting", IE_Pressed, this, &ADBPlayerController::OnStartTargeting);
	InputComponent->BindAction("Targeting", IE_Released, this, &ADBPlayerController::OnStopTargeting);

	InputComponent->BindAction("Fire", IE_Pressed, this, &ADBPlayerController::OnStartFire);
	InputComponent->BindAction("Fire", IE_Released, this, &ADBPlayerController::OnStopFire);
	InputComponent->BindAction("Reload", IE_Pressed, this, &ADBPlayerController::OnReload);

	InputComponent->BindAction("PrevWeapon", IE_Pressed, this, &ADBPlayerController::OnPrevWeapon);
	InputComponent->BindAction("NextWeapon", IE_Pressed, this, &ADBPlayerController::OnNextWeapon);

	InputComponent->BindAction("InteractWithItem", IE_Pressed, this, &ADBPlayerController::OnInteractWithItem);
	InputComponent->BindAction("Drop", IE_Pressed, this, &ADBPlayerController::OnDropItem);

	InputComponent->BindAction("SwitchCameraMode", IE_Pressed, this, &ADBPlayerController::OnSwitchCameraMode);

	InputComponent->BindAction("Esc", IE_Pressed, this, &ADBPlayerController::OnConsultESC);


}

void ADBPlayerController::MoveForward(float Delta)
{
	if (m_CanReceiveInput && Delta != 0.f && m_ControlledCharacter != nullptr)
	{
		m_ControlledCharacter->MoveForward(Delta);
	}
}

void ADBPlayerController::MoveRight(float Delta)
{
	if (m_CanReceiveInput && Delta != 0.f && m_ControlledCharacter != nullptr)
	{
		m_ControlledCharacter->MoveRight(Delta);
	}
}

void ADBPlayerController::CustomAddPitchInput(float Delta)
{
	if (m_CanReceiveInput && Delta != 0.f && m_ControlledCharacter != nullptr)
	{
		m_ControlledCharacter->AddPitchInput(Delta);
	}
}

void ADBPlayerController::CustomAddYawInput(float Delta)
{
	if (m_CanReceiveInput && Delta != 0.f && m_ControlledCharacter != nullptr)
	{
		m_ControlledCharacter->AddYawInput(Delta);
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
	if (m_CanReceiveInput && m_ControlledCharacter != nullptr)
	{
		new(m_DeferredFireInputs)FDeferredFireInput(true);
	}
}

void ADBPlayerController::OnStopFire()
{
	if (m_CanReceiveInput && m_ControlledCharacter != nullptr)
	{
		new(m_DeferredFireInputs)FDeferredFireInput(false);
	}
}

void ADBPlayerController::OnReload()
{
	if (m_CanReceiveInput && m_ControlledCharacter != nullptr)
	{
		m_ControlledCharacter->OnReloadAmmo();
	}
}

void ADBPlayerController::ApplyDeferredFireInputs()
{
	if (m_CanReceiveInput && m_ControlledCharacter == nullptr)
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

void ADBPlayerController::OnStartTargeting()
{
	if (m_CanReceiveInput && m_ControlledCharacter != nullptr)
	{
		m_ControlledCharacter->OnStartTargeting();
	}
}

void ADBPlayerController::OnStopTargeting()
{
	if (m_CanReceiveInput && m_ControlledCharacter != nullptr)
	{
		m_ControlledCharacter->OnStopTargeting();
	}
}

void ADBPlayerController::OnPrevWeapon()
{
	if (m_CanReceiveInput && m_ControlledCharacter)
	{
		m_ControlledCharacter->SwitchEquipHandWeapon(false);
	}
}

void ADBPlayerController::OnNextWeapon()
{
	if (m_CanReceiveInput && m_ControlledCharacter)
	{
		m_ControlledCharacter->SwitchEquipHandWeapon(true);
	}
}

void ADBPlayerController::OnSwitchCameraMode()
{
	if (m_CanReceiveInput && m_ControlledCharacter)
	{
		m_ControlledCharacter->SwitchCamaraMode();
	}
}

void ADBPlayerController::OnInteractWithItem()
{
	if (m_CanReceiveInput && m_ControlledCharacter)
	{
		m_ControlledCharacter->InteractWithItem();
	}
}

void ADBPlayerController::OnDropItem()
{
	if (m_CanReceiveInput && m_ControlledCharacter)
	{
		m_ControlledCharacter->DropItem(false);
	}
}

void ADBPlayerController::OnConsultESC()
{
	if (m_ControlledCharacter)
	{
		UEventSets::Instance()->OnCallESC.Broadcast();
	}
}

// -----------------------------GameMode....
void ADBPlayerController::EnterState(EPlayerInGameState State)
{
	PlayerInGameState = State;

	switch (State)
	{
	case EPlayerInGameState::PrepareForGettingIn:
	{
		UEventSets::Instance()->OnPreparedForGetInGame.Broadcast();
	}
	break;

	default:
		;
	}

}

void ADBPlayerController::Spawn()
{
	ADBBattleGameModeBase* GameMode = Cast<ADBBattleGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->SpawnPlayer(this);
	}
}

void ADBPlayerController::SetCanReceiveInput(bool CanReceive)
{
	m_CanReceiveInput = CanReceive;
}
