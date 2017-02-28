// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBCharacterAnimInstance.h"
#include "GameLogic/Character/DBCharacter.h"

ADBCharacter* UDBCharacterAnimInstance::GetCharacter() const
{
	AActor* TOwner = GetOwningActor();
	if (!TOwner)
	{
		return nullptr;
	}

	ADBCharacter* TDBCharacter = Cast<ADBCharacter>(TOwner);

	return TDBCharacter;
}