// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/CharacterMovementComponent.h"
#include "DBCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API UDBCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	bool Is3DSpaceFreeMove() const;


	
};
