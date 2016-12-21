// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DPlayerCameraManager.h"
#include "DPlayerCharacter.h"

class ADPlayerCharacter;

ADPlayerCameraManager::ADPlayerCameraManager(const FObjectInitializer & ObjectInitializer)
	:Super(ObjectInitializer)
{
	mDefaultFOV = 90.f;
	mTargetFOV = 65.f;
}

void ADPlayerCameraManager::UpdateCamera(float DeltaTime)
{
	ADPlayerCharacter* MyPawn = PCOwner ? Cast<ADPlayerCharacter>(PCOwner->GetPawn()) : nullptr;
	if (MyPawn)
	{
		float newFOV;
		if (MyPawn->IsTargeting())
		{
			MyPawn->SetCameraPos(DeltaTime, true);
			newFOV = mTargetFOV;
		}
		else
		{
			MyPawn->SetCameraPos(DeltaTime, false);
			newFOV = mDefaultFOV;
		}
		
		DefaultFOV = FMath::FInterpTo(DefaultFOV, newFOV, DeltaTime, 10.f);
		SetFOV(DefaultFOV);
	}

	Super::UpdateCamera(DeltaTime);
}
