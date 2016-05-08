// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DPlayerMovementComponent.h"
#include "DPlayerCharacter.h"

UDPlayerMovementComponent::UDPlayerMovementComponent()
{
}

float UDPlayerMovementComponent::GetMaxSpeed() const
{
	float MaxSpeed = Super::GetMaxSpeed();

	const ADPlayerCharacter* DPlayer = Cast<ADPlayerCharacter>(CharacterOwner);
	if (DPlayer)
	{
		if (DPlayer->IsTargeting())
		{
			MaxSpeed *= DPlayer->GetTargetingSpeedModifier();
		}
		if (DPlayer->IsRunning())
		{
			MaxSpeed *= DPlayer->GetRunningSpeedModifier();
		}
	}

	return MaxSpeed;
}
