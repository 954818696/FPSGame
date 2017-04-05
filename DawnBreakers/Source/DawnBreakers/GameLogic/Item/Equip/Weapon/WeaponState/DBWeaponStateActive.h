// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DBWeaponStateBase.h"
#include "DBWeaponStateActive.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API UDBWeaponStateActive : public UDBWeaponStateBase
{
	GENERATED_UCLASS_BODY()

public:
	
	virtual void EnterWeaponState();

	virtual void ExitWeaponState();

	virtual bool CanTransferTo(EWeaponState::Type NewState, UDBWeaponStateBase* State);
	
	
};
