// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DPlayerCharacter.h"


// Sets default values
ADPlayerCharacter::ADPlayerCharacter(const FObjectInitializer& ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mbIsTargeting = false;
	mbWantsToRun = false;
	mbIsJumping = false;
}

// Called when the game starts or when spawned
void ADPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADPlayerCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ADPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &ADPlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ADPlayerCharacter::MoveRight);
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	


	InputComponent->BindAction("Fire", IE_Pressed, this, &ADPlayerCharacter::OnStartFire);
	InputComponent->BindAction("Fire", IE_Released, this, &ADPlayerCharacter::OnStopFire);
	InputComponent->BindAction("Targeting", IE_Pressed, this, &ADPlayerCharacter::OnStartTargeting);
	InputComponent->BindAction("Targeting", IE_Released, this, &ADPlayerCharacter::OnStopTargeting);


}

void ADPlayerCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ADPlayerCharacter, mbIsTargeting, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(ADPlayerCharacter, mbWantsToRun, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(ADPlayerCharacter, mbIsJumping, COND_SkipOwner);

}

void ADPlayerCharacter::MoveForward(float val)
{
	if (Controller && val != 0.f)
	{
		const bool bLimitRotation = (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling());
		const FRotator Rotation = bLimitRotation ? GetActorRotation() : Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, val);
	}
}

void ADPlayerCharacter::MoveRight(float val)
{
	if (val != 0)
	{
		const FQuat Rotation = GetActorQuat();
		const FVector Direction = FQuatRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, val);
	}
}

void ADPlayerCharacter::OnCrouchToggle()
{
	if (IsRunning())
	{
		SetRunning(false);
	}

	if (CanCrouch())
	{
		Crouch();
	}
	else
	{
		UnCrouch();
	}
}



void ADPlayerCharacter::OnStartFire()
{
}

void ADPlayerCharacter::OnStopFire()
{
}

void ADPlayerCharacter::StartWeaponFire()
{
}

void ADPlayerCharacter::StopWeaponFire()
{
}

void ADPlayerCharacter::OnStartTargeting()
{
	if (IsRunning())
	{
		SetRunning(false);
	}
	SetTargeting(true);
}

void ADPlayerCharacter::OnStopTargeting()
{
	SetTargeting(false);
}

void ADPlayerCharacter::SetTargeting(bool bNewTargeting)
{
	mbIsTargeting = bNewTargeting;
	if (Role < ROLE_Authority)
	{
		ServerSetTargeting(bNewTargeting);
	}
}

bool ADPlayerCharacter::ServerSetTargeting_Validate(bool bNewTargeting)
{
	return true;
}

void ADPlayerCharacter::ServerSetTargeting_Implementation(bool bNewTargeting)
{
	SetTargeting(bNewTargeting);
}

void ADPlayerCharacter::OnNextWeapon()
{
}

void ADPlayerCharacter::OnPrevWeapon()
{
}

void ADPlayerCharacter::OnReload()
{
}

void ADPlayerCharacter::OnStartJump()
{
	bPressedJump = true;
	SetIsJumping(true);
}

void ADPlayerCharacter::OnStopJump()
{
	bPressedJump = false;
}

void ADPlayerCharacter::SetIsJumping(bool NewJumping)
{
	if (bIsCrouched && NewJumping)
	{
		UnCrouch();
	}
	else
	{
		mbIsJumping = NewJumping;
	}

	if (Role < ROLE_Authority)
	{
		ServerSetIsJumping(NewJumping);
	}
}

void ADPlayerCharacter::ServerSetIsJumping_Implementation(bool NewJumping)
{
	SetIsJumping(NewJumping);
}

bool ADPlayerCharacter::ServerSetIsJumping_Validate(bool NewJumping)
{
	return true;
}

void ADPlayerCharacter::OnStartRunning()
{
	if (IsTargeting())
	{
		SetTargeting(false);
	}
	StopWeaponFire();
	SetRunning(true);
}

void ADPlayerCharacter::OnStopRunning()
{
	SetRunning(false);
}

void ADPlayerCharacter::SetRunning(bool bNewRunning)
{
	mbWantsToRun = true;

	if (bIsCrouched)
	{
		UnCrouch();
	}

	if (Role < ROLE_Authority)
	{
		ServerSetRunning(bNewRunning);
	}
	UpdateRunSounds(bNewRunning);
}

bool ADPlayerCharacter::IsRunning() const
{
	if (!GetCharacterMovement())
	{
		return false;
	}

	return mbWantsToRun  && !GetVelocity().IsZero() && (GetVelocity().GetSafeNormal2D() | GetActorForwardVector()) > -0.1;
}

bool ADPlayerCharacter::ServerSetRunning_Validate(bool bNewRunning)
{
	return true;
}

void ADPlayerCharacter::ServerSetRunning_Implementation(bool bNewRunning)
{
	SetRunning(bNewRunning);
}


void ADPlayerCharacter::UpdateRunSounds(bool bNewRunning)
{

}

bool ADPlayerCharacter::IsTargeting() const
{
	return mbIsTargeting;
}

void ADPlayerCharacter::PostInitializeComponents()
{
}

void ADPlayerCharacter::Destroyed()
{
}



float ADPlayerCharacter::PlayAnimMontage(UAnimMontage * AnimMontage, float InPlayRate, FName StartSectionName)
{
	return 0.0f;
}

void ADPlayerCharacter::StopAnimMontage(UAnimMontage * AnimMontage)
{
}

void ADPlayerCharacter::StopAllAnimMontages()
{
}

void ADPlayerCharacter::test()
{
}

