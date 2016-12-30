// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "DBWeaponStateMachine.generated.h"

/**
 * 
 */
UCLASS(DefaultToInstanced, EditInlineNew)
class DAWNBREAKERS_API UDBWeaponStateMachine : public UObject
{
	GENERATED_BODY()
	
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Inner")
	float InnerValue;

	
};
