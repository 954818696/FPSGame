// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBDamageType.h"

UDBDamageType::UDBDamageType(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	HeadDmgModifier = 3.0f;
	LimbDmgModifier = 0.5f;

	bCanDieFrom = true;
}



bool UDBDamageType::GetCanDieFrom()
{
	return bCanDieFrom;
}

float UDBDamageType::GetHeadDamageModifier()
{
	return HeadDmgModifier;
}

float UDBDamageType::GetLimbDamageModifier()
{
	return LimbDmgModifier;
}
