// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBCharacterMovementComponent.h"
#include "Player/DBPlayerController.h"

UDBCharacterMovementComponent::UDBCharacterMovementComponent(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void UDBCharacterMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CharacterOwner != nullptr)
	{
		ADBPlayerController* PC = Cast<ADBPlayerController>(CharacterOwner->Controller);
		if (PC != nullptr && PC->PlayerInput != nullptr)
		{
			PC->ApplyDeferredFireInputs();
		}
	}
}

bool UDBCharacterMovementComponent::Is3DSpaceFreeMove() const
{
	return (MovementMode == MOVE_Flying) || (MovementMode == MOVE_Swimming);
}
