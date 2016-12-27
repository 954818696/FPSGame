// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DPlayerCharacter.h"
#include "DPlayerMovementComponent.h"


// Sets default values
ADPlayerCharacter::ADPlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UDPlayerMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 运动控制
	UCharacterMovementComponent* MoveComp = GetCharacterMovement();
	MoveComp->GravityScale = 1.5f;
	MoveComp->JumpZVelocity = 620;
	MoveComp->bCanWalkOffLedgesWhenCrouching = true;
	MoveComp->MaxWalkSpeedCrouched = 100;

	
	// 镜头控制
	// fps camera.
	//mCameraFP = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("CameraFp"));
	//mCameraFP->bUsePawnControlRotation = true;
	//mCameraFP->AttachParent = GetMesh();

	// third person camera.
	mCameraBoomComp = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	mCameraBoomComp->SocketOffset = FVector(0, 35, 0);
	mCameraBoomComp->TargetOffset = FVector(0, 0, 55);
	mCameraBoomComp->bUsePawnControlRotation = true;
	//mCameraBoomComp->AttachParent = GetRootComponent();
	mCameraBoomComp->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	//mCameraTP = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("CameraTP"));
	//mCameraTP->AttachParent = mCameraBoomComp;

	// 角色全身模型
	//GetMesh()->bOnlyOwnerSee = false;
	//GetMesh()->bOwnerNoSee = true;
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

	// 状态变量初始化
	mbIsTargeting = false;
	mbWantsToRun = false;
	mbIsJumping = false;

	mfTargetingSpeedModifier = 0.5f;
	mfRunningSpeedModifier = 1.5f;
}

// Called when the game starts or when spawned
void ADPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//mCameraFP->RelativeLocation = mFPSCameraPos.GetLocation();
	
}

// Called every frame
void ADPlayerCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
//void ADPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
//{
//	Super::SetupPlayerInputComponent();
//
//	InputComponent->BindAxis("MoveForward", this, &ADPlayerCharacter::MoveForward);
//	InputComponent->BindAxis("MoveRight", this, &ADPlayerCharacter::MoveRight);
//	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
//	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
//	
//
//	InputComponent->BindAction("Jump", IE_Pressed, this, &ADPlayerCharacter::OnStartJump);
//	InputComponent->BindAction("Jump", IE_Released, this, &ADPlayerCharacter::OnStopJump);
//	InputComponent->BindAction("CrouchToggle", IE_Released, this, &ADPlayerCharacter::OnCrouchToggle);
//	InputComponent->BindAction("Targeting", IE_Pressed, this, &ADPlayerCharacter::OnStartTargeting);
//	InputComponent->BindAction("Targeting", IE_Released, this, &ADPlayerCharacter::OnStopTargeting);
//
//	InputComponent->BindAction("Fire", IE_Pressed, this, &ADPlayerCharacter::OnStartFire);
//	InputComponent->BindAction("Fire", IE_Released, this, &ADPlayerCharacter::OnStopFire);
//
//
//}

void ADPlayerCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

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

FRotator ADPlayerCharacter::GetAimOffsets() const
{
	const FVector AimDirWS = GetBaseAimRotation().Vector();
	const FVector AimDirLS = ActorToWorld().InverseTransformVectorNoScale(AimDirWS);
	const FRotator AimRotLS = AimDirLS.Rotation();

	return AimRotLS;
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
}

float ADPlayerCharacter::GetTargetingSpeedModifier() const
{
	return mfTargetingSpeedModifier;
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
	SetIsJumping(false);
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

bool ADPlayerCharacter::IsInitJumping() const
{
	return mbIsJumping;
}

float ADPlayerCharacter::GetRunningSpeedModifier() const
{
	return mfRunningSpeedModifier;
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
	Super::PostInitializeComponents();
}

void ADPlayerCharacter::Destroyed()
{
	Super::Destroyed();
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

FName ADPlayerCharacter::GetWeaponAttachPoint() const
{
	return FName();
}

void ADPlayerCharacter::SetCameraPos(float deltaTime, bool bAim)
{
	float tX, tY, tZ;

	if (bAim)
	{
		tX = mAimCameraPos.GetLocation().X;
		tY = mAimCameraPos.GetLocation().Y;
		tZ = mAimCameraPos.GetLocation().Z;
	}
	else
	{
		tX = mFPSCameraPos.GetLocation().X;
		tY = mFPSCameraPos.GetLocation().Y;
		tZ = mFPSCameraPos.GetLocation().Z;
	}

	if (mCameraFP)
	{
		mCameraFP->RelativeLocation.X = FMath::FInterpTo(mCameraFP->RelativeLocation.X, tX, deltaTime, 10.f);
		mCameraFP->RelativeLocation.Y = FMath::FInterpTo(mCameraFP->RelativeLocation.Y, tY, deltaTime, 10.f);
		mCameraFP->RelativeLocation.Z = FMath::FInterpTo(mCameraFP->RelativeLocation.Z, tZ, deltaTime, 10.f);
	}

}

void ADPlayerCharacter::SwitchCameraMode()
{
//	mCameraFP->AttachParent = mCameraBoomComp;
}

