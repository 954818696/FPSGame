// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBCharacterMovementComponent.h"




bool UDBCharacterMovementComponent::Is3DSpaceFreeMove() const
{
	return (MovementMode == MOVE_Flying) || (MovementMode == MOVE_Swimming);
}
