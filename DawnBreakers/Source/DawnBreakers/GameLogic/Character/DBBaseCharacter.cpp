// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBBaseCharacter.h"


// Sets default values
ADBBaseCharacter::ADBBaseCharacter(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Character Mesh Configuration.
	GetMesh()->bReceivesDecals = false;
	GetMesh()->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::AlwaysTickPoseAndRefreshBones;
	GetMesh()->SetCollisionObjectType(ECC_Pawn);

	GetMesh()->SetCollisionResponseToChannel(COLLISION_WEAPON_INST, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(COLLISION_WEAPON_PROJ, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);


	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_WEAPON_INST, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_WEAPON_PROJ, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f, false);
	GetCapsuleComponent()->SetCapsuleRadius(42.0f);

	//GetMovementComponent()->NavAgentProps.AgentRadius = 42;
	//GetMovementComponent()->NavAgentProps.AgentHeight = 192;

	Health = 100.f;
	SprintingSpeedModifier = 1.f;
}

// Called when the game starts or when spawned
void ADBBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADBBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADBBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool ADBBaseCharacter::IsAlive() const
{
	return Health > 0;
}

bool ADBBaseCharacter::IsSprinting() const
{
	return false;
}

void ADBBaseCharacter::PlayHit(float DamageTaken, struct FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser, bool bKilled)
{

}

