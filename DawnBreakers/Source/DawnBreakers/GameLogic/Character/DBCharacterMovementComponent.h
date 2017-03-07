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
	GENERATED_UCLASS_BODY()
	
public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	bool Is3DSpaceFreeMove() const;


	
};
