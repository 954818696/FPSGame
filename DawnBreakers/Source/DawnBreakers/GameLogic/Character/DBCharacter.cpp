// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBCharacter.h"
#include "DBCharacterMovementComponent.h"


// Sets default values
ADBCharacter::ADBCharacter(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UDBCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_CharacterMovement = Cast<UDBCharacterMovementComponent>(GetCharacterMovement());
}

// Called when the game starts or when spawned
void ADBCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADBCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ADBCharacter::MoveForward(float Delta)
{
	if (Delta != 0)
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation = (m_CharacterMovement && m_CharacterMovement->Is3DSpaceFreeMove()) ? Rotation : FRotator(0, Rotation.Yaw, 0);

		AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X), Delta);
	}
}

void ADBCharacter::MoveRight(float Delta)
{
	if (Delta != 0)
	{

		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y), Delta);
	}
}

