// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBCharacter.h"
#include "DBCharacterMovementComponent.h"
#include "GameLogic/Equip/Weapon/DBWeaponBase.h"
#include "GameLogic/Equip/Inventory/DBInventory.h"

ADBCharacter::ADBCharacter(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UDBCharacterMovementComponent>(ACharacter::CharacterMovementComponentName)),
	m_CurCameraMode(ECameraMode::E_FirstPersonPerspective)
{
	PrimaryActorTick.bCanEverTick = true;
	
	// CharacterMovement Configuration.
	m_CharacterMovement = Cast<UDBCharacterMovementComponent>(GetCharacterMovement());
	m_CharacterMovement->GravityScale = 1.5f;
	m_CharacterMovement->JumpZVelocity = 620;
	m_CharacterMovement->bCanWalkOffLedgesWhenCrouching = true;
	m_CharacterMovement->MaxWalkSpeedCrouched = 100;

	// Character Mesh Configuration.
	GetMesh()->bReceivesDecals = false;
	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//GetMesh()->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Block);
	//GetMesh()->SetCollisionResponseToChannel(COLLISION_PROJECTILE, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetCapsuleHalfHeight(90.f);
	GetCapsuleComponent()->SetCapsuleRadius(30.f);

	// Camera Configuration.
	m_CameraComp = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("CharacterCamera"));
	m_CameraComp->bUsePawnControlRotation = true;

	m_CameraBoomComp = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	m_CameraBoomComp->SocketOffset = FVector(0, 35, 0);
	//m_CameraBoomComp->TargetOffset = FVector(0, 0, 55);
	m_CameraBoomComp->bUsePawnControlRotation = true;
	m_CameraBoomComp->SetupAttachment(GetRootComponent());
}

void ADBCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	SetDefaultEquipWeapon();
	SetFPSCamera();
}

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

void ADBCharacter::OnStartJump()
{

}

void ADBCharacter::OnStopJump()
{

}

void ADBCharacter::OnStartFire()
{
#ifdef DEBUG_FIRE
	FVector CamLoc;
	FRotator CamRot;
	Controller->GetPlayerViewPoint(CamLoc, CamRot);
	const FVector TraceStart = CamLoc;
	const FVector Direction = CamRot.Vector();
	const FVector TraceEnd = TraceStart + (Direction * 10000);
	FHitResult Hit(ForceInit);
	FCollisionQueryParams TraceParams(TEXT("HitTest"), true, this);
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, TraceParams);
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 20.0f, 0, 5);
	DrawDebugPoint(GetWorld(), Hit.Location, 10, FColor(255, 0, 255), false, 20);
#endif

	m_Weapon->OnStartFire();
	
}

void ADBCharacter::OnStopFire()
{
	DAWNBREAKERS_LOG_INFO("ADBCharacter::OnStopFire");

	m_Weapon->OnStopFire();
}

void ADBCharacter::OnStartTargeting()
{
	SetTargeting(true);
}

void ADBCharacter::OnStopTargeting()
{
	SetTargeting(false);
}

void ADBCharacter::SwitchEquipWeapon(bool bNext)
{

}


void ADBCharacter::InitDefaultInventory()
{

}

void ADBCharacter::SetDefaultEquipWeapon()
{

}

void ADBCharacter::SetTargeting(bool bNewTargeting)
{

}

void ADBCharacter::SetFPSCamera()
{
	m_CameraComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("head")));
	m_CameraComp->RelativeLocation = m_FPSCameraPos.GetLocation();
	m_CurCameraMode = ECameraMode::E_FirstPersonPerspective;
}

void ADBCharacter::SwitchCamaraMode()
{
	if (m_CurCameraMode == ECameraMode::E_FirstPersonPerspective)
	{
		m_CurCameraMode = ECameraMode::E_ThirdPersonPerspective;
		m_CameraComp->AttachToComponent(m_CameraBoomComp, FAttachmentTransformRules::KeepRelativeTransform);
		m_CameraComp->RelativeLocation = FVector::ZeroVector;
	}
	else 
	{
		SetFPSCamera();
	}
}




