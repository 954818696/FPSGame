// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBCharacter.h"
#include "DBCharacterMovementComponent.h"
#include "GameLogic/Animation/AnimInstance/DBCharacterAnimInstance.h"
#include "GameLogic/Item/Equip/Weapon/ShootWeapon/DBShootWeaponBase.h"
#include "GameLogic/Item/Equip/Inventory/DBInventoryBase.h"

#define DEFAULT_FOV 90.f
#define MAX_ARM_LAG_ROT 20.f

ADBCharacter::ADBCharacter(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UDBCharacterMovementComponent>(ACharacter::CharacterMovementComponentName)),
	m_CurCameraMode(ECameraMode::E_FirstPersonPerspective),
	m_MaxInteractableDistance(400.f),
	m_PrevViewPitchRotation(0.f),
	m_PrevViewYawRotation(0.f),
	m_PendEquipWeapon(nullptr),
	m_HoldWeapon(nullptr),
	m_AnimationInstance(nullptr)
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
	GetMesh()->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::AlwaysTickPoseAndRefreshBones;
	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	//GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);
	//GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	//GetMesh()->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Block);
	//GetMesh()->SetCollisionResponseToChannel(COLLISION_PROJECTILE, ECR_Block);
	//GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	//GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
	//GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	

	GetCapsuleComponent()->SetCapsuleHalfHeight(90.f);
	GetCapsuleComponent()->SetCapsuleRadius(30.f);

	// Camera Configuration.
	m_CameraComp = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("CharacterCamera"));
	m_CameraComp->bUsePawnControlRotation = true;

	m_CameraBoomComp = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	m_CameraBoomComp->SocketOffset = FVector(0, 35, 0);
	m_CameraBoomComp->bUsePawnControlRotation = true;
	m_CameraBoomComp->SetupAttachment(GetRootComponent());
}

void ADBCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	SetFPSCamera();

	CreateInventory();
}


void ADBCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	InteractQueryTick();

	// UpperBody Rotate.
	const float TViewPitch = Controller->GetControlRotation().Pitch;
	const float TViewYaw = GetActorRotation().Yaw;
	const float TNewPitchLag = FMath::ClampAngle((TViewPitch - m_PrevViewPitchRotation) * 2.f, -MAX_ARM_LAG_ROT, MAX_ARM_LAG_ROT);
	const float TNewYawLag = FMath::ClampAngle((m_PrevViewYawRotation - TViewYaw) * 2.f, -MAX_ARM_LAG_ROT, MAX_ARM_LAG_ROT);
	m_ArmsLagRotation = FMath::RInterpTo(m_ArmsLagRotation, FRotator(TNewPitchLag, TNewYawLag, TNewYawLag), DeltaTime, 8.f);
	m_PrevViewPitchRotation = TViewPitch;
	m_PrevViewYawRotation = TViewYaw;
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

void ADBCharacter::AddYawInput(float Delta)
{
	Super::AddControllerYawInput(Delta * m_CameraComp->FieldOfView / DEFAULT_FOV);
}

void ADBCharacter::AddPitchInput(float Delta)
{
	Super::AddControllerPitchInput(Delta * m_CameraComp->FieldOfView / DEFAULT_FOV);
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
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.f);
	DrawDebugPoint(GetWorld(), Hit.Location, 10, FColor(255, 0, 255), false, 1.f);
#endif
}

void ADBCharacter::OnStopFire()
{
	DAWNBREAKERS_LOG_INFO("ADBCharacter::OnStopFire");

}

void ADBCharacter::OnStartTargeting()
{
	if (m_HoldWeapon)
	{
		SetTargeting(true);
	}
}

void ADBCharacter::OnStopTargeting()
{
	SetTargeting(false);
}

void ADBCharacter::InteractWithItem()
{
	if (m_FocusedInteractItem == nullptr || !m_FocusedInteractItem->IsValidLowLevelFast())
	{
		return;
	}

	// 1.Pick Up.
	if (m_FocusedInteractItem->IsA(ADBInventoryItemBase::StaticClass()))
	{
		ADBInventoryItemBase* InventoryItem = Cast<ADBInventoryItemBase>(m_FocusedInteractItem);
		OnPickUpItem(InventoryItem);
	}
	// 2.Interact With
	else
	{
		// My Great OS In the Future.
	}
}

void ADBCharacter::OnPickUpItem(class ADBInventoryItemBase* NewItem)
{
	if (NewItem == nullptr || NewItem->IsValidLowLevel() == false)
	{
		return;
	}

//	NewWeapon->ConfigAttachToTargetSceneComponent(GetMesh());
	// 非武器物品直接进背包，如果是枪，近战武器则考虑是否直接装备
	bool bCanAddToInventory = m_Inventory->AddToInventory(NewItem);
	if (bCanAddToInventory)
	{
		if (NewItem->IsA(ADBShootWeaponBase::StaticClass()))
		{
			// 手中无握持武器,直接装备
			ADBWeaponBase* NewWeapon = Cast<ADBWeaponBase>(NewItem);
			if (!m_HoldWeapon)
			{
				EquipHandWeapon(NewWeapon, false);
			}
			// 手中有握持武器
			// 1.相同握持优先级别，或比手中武器握持优先级高，则将手中武器放入背包，然后装备捡起的武器。
			// 2.低握持优先级，直接进入背包
			else
			{
				PutHandWeaponToInventory();
				m_bPendEquipFromInventory = false;
				m_PendEquipWeapon = NewWeapon;
			}
		}
	}
}

void ADBCharacter::EquipHandWeapon(ADBWeaponBase* NewWeapon, bool bEquipedWeaponFromInventory)
{
	if (NewWeapon && NewWeapon->IsValidLowLevel())
	{
		NewWeapon->OnEquip(bEquipedWeaponFromInventory);
	}
}

void ADBCharacter::PutHandWeaponToInventory()
{
	if (m_HoldWeapon && m_HoldWeapon->IsValidLowLevelFast())
	{
		m_HoldWeapon->OnUnEquip();
		GetWorldTimerManager().SetTimer(TimerHandle_PendWeaponEquip, this, &ADBCharacter::EquipPendedWeapon, 1.f, true);
	}
}

void ADBCharacter::EquipPendedWeapon()
{
	if (m_HoldWeapon == nullptr)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_PendWeaponEquip);
		EquipHandWeapon(m_PendEquipWeapon, m_bPendEquipFromInventory);
	}
}

void ADBCharacter::SwitchEquipHandWeapon(bool bNext)
{
	if (m_Inventory && m_Inventory->IsValidLowLevel())
	{
		ADBWeaponBase* SwitchWeapon = Cast<ADBWeaponBase>(m_Inventory->GetOneItemByItemSequence(m_HoldWeapon, bNext));
		if (SwitchWeapon)
		{
			m_IsTargeting = false;
			PutHandWeaponToInventory();
			m_bPendEquipFromInventory = true;
			m_PendEquipWeapon = SwitchWeapon;
		}
	}
}


void ADBCharacter::CreateInventory()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	m_Inventory = GetWorld()->SpawnActor<ADBInventoryBase>(m_InventoryClass ,SpawnInfo);
	if (m_Inventory && m_Inventory->IsValidLowLevel())
	{
		m_Inventory->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		m_Inventory->SetItemOwner(this);
	}
}

float ADBCharacter::GetViewPitch() const
{
	if (Controller)
	{
		return Controller->GetControlRotation().Pitch;
	}

	return 0;
}

void ADBCharacter::GetArmRotation(FRotator & OutRotation) const
{
	OutRotation = m_ArmsLagRotation;
}

UDBCharacterAnimInstance* ADBCharacter::GetAnimInstance()
{
	if (m_AnimationInstance == NULL && GetMesh() != NULL)
	{
		m_AnimationInstance = Cast<UDBCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	}
	return m_AnimationInstance;
}

void ADBCharacter::InteractQueryTick()
{
	if (Controller && Controller->IsLocalController())
	{
		AActor* InteractedItem = QueryItemByRay();

		if (InteractedItem)
		{
			IItemInteractInterface* IItemInteract = Cast<IItemInteractInterface>(InteractedItem);
			if (IItemInteract)
			{
				if (m_FocusedInteractItem != InteractedItem)
				{
					IItemInteract->SetInteractFocus();
					if (m_FocusedInteractItem)
					{
						IItemInteractInterface* IItemInteractPrev = Cast<IItemInteractInterface>(InteractedItem);
						if (IItemInteractPrev)
						{
							IItemInteractPrev->LoseInteractFocus();
						}
					}
					m_FocusedInteractItem = InteractedItem;
				}
			}
		}
		else
		{
			if (m_FocusedInteractItem)
			{
				IItemInteractInterface* IItemInteractPrev = Cast<IItemInteractInterface>(m_FocusedInteractItem);
				IItemInteractPrev->LoseInteractFocus();
			}
			m_FocusedInteractItem = nullptr;
		}
	}
}

AActor* ADBCharacter::QueryItemByRay()
{
	FVector   CamLocation;
	FRotator CamRotator;
	Controller->GetPlayerViewPoint(CamLocation, CamRotator);

	const FVector TraceStart = CamLocation;
	const FVector Direction = CamRotator.Vector();
	const FVector TraceEnd = TraceStart + (Direction * m_MaxInteractableDistance);

	FCollisionQueryParams TraceParams(TEXT("TraceItem"), true, this);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.bTraceComplex = false;
	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, TraceParams);
    //DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f);
	//DrawDebugPoint(GetWorld(), Hit.Location, 10, FColor(255, 0, 255), false, 1.f);

	return Hit.GetActor();
}

void ADBCharacter::SetTargeting(bool bNewTargeting)
{
	m_IsTargeting = bNewTargeting;
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

void ADBCharacter::SetCameraAim(float Delta, bool bAim)
{
	if (m_CurCameraMode == ECameraMode::E_FirstPersonPerspective)
	{
		if (bAim)
		{
			//tX = mAimCameraPos.GetLocation().X;
			//tY = mAimCameraPos.GetLocation().Y;
			//tZ = mAimCameraPos.GetLocation().Z;
			m_CameraComp->RelativeLocation = FMath::VInterpTo(m_CameraComp->RelativeLocation, m_HoldWeapon->GetMeshComp()->GetSocketLocation(FName(TEXT("IronSight"))), Delta, 10.f);

		}
		else
		{
			// 4 , 5, -7  rifle.
			m_CameraComp->RelativeLocation = FMath::VInterpTo(m_CameraComp->RelativeLocation, FVector(4.f, 5.f, -7.f), Delta, 10.f);
		}
	}
}




