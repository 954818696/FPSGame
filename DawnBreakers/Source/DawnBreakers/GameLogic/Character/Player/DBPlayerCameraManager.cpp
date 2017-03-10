// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBPlayerCameraManager.h"

ADBPlayerCameraManager::ADBPlayerCameraManager(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_DefaultFOV = 90.f;
	m_TargetFOV = 65.f;
}



void ADBPlayerCameraManager::UpdateCamera(float DeltaTime)
{
	ADBCharacter* TCharacter = PCOwner ? Cast<ADBCharacter>(PCOwner->GetPawn()) : nullptr;
	if (TCharacter)
	{
		float NewFOV;
		if (TCharacter->IsTargeting())
		{
			TCharacter->SetCameraAim(DeltaTime, true);
			NewFOV = m_TargetFOV;
		}
		else
		{
			TCharacter->SetCameraAim(DeltaTime, false);
			NewFOV = m_DefaultFOV;
		}

		DefaultFOV = FMath::FInterpTo(DefaultFOV, NewFOV, DeltaTime, 10.f);
		SetFOV(DefaultFOV);
	}

	Super::UpdateCamera(DeltaTime);
}
