// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "DBDamageType.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API UDBDamageType : public UDamageType
{
	GENERATED_UCLASS_BODY()
	
public:
	bool GetCanDieFrom();

	float GetHeadDamageModifier();

	float GetLimbDamageModifier();

protected:
	UPROPERTY(EditDefaultsOnly)
	bool bCanDieFrom;

	UPROPERTY(EditDefaultsOnly)
	float HeadDmgModifier;

	UPROPERTY(EditDefaultsOnly)
	float LimbDmgModifier;
	
};
