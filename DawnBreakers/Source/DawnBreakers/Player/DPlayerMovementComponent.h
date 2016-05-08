// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/MovementComponent.h"
#include "DPlayerMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API UDPlayerMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UDPlayerMovementComponent();

	virtual float GetMaxSpeed() const override;
	
	
};
