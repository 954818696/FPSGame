// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBCharacter.h"
#include "GameLogic/Character/Player/Movement/DBCharacterMovementComponent.h"
#include "GameLogic/Animation/AnimInstance/DBCharacterAnimInstance.h"
#include "GameLogic/Item/Equip/Weapon/ShootWeapon/DBShootWeaponBase.h"
#include "GameLogic/Item/Equip/Inventory/DBInventoryBase.h"
#include "GameLogic/Character/Player/Controller/DBPlayerController.h"

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
	if (m_HoldWeapon)
	{
		m_HoldWeapon->OnStartFire();
	}
}

void ADBCharacter::OnStopFire()
{
	if (m_HoldWeapon)
	{
		m_HoldWeapon->OnStopFire();
	}
}

void ADBCharacter::OnReloadAmmo()
{
	if (m_HoldWeapon && m_HoldWeapon->IsA(ADBShootWeaponBase::StaticClass()))
	{
		m_IsTargeting = false;
		ADBShootWeaponBase* ShootWeapon = Cast<ADBShootWeaponBase>(m_HoldWeapon);
		ShootWeapon->OnReload();
	}
}

void ADBCharacter::OnStartTargeting()
{
	if (m_HoldWeapon && m_HoldWeapon->IsA(ADBShootWeaponBase::StaticClass()))
	{
		m_IsTargeting = true;
	}
}

void ADBCharacter::OnStopTargeting()
{
	m_IsTargeting = false;
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

FVector ADBCharacter::GetFiringDirection()
{
	ADBPlayerController* TPlayerController = Cast<ADBPlayerController>(GetController());
	FVector OutDirection;

	if (TPlayerController)
	{
		FVector TCamLoc;
		FRotator TCamRot;
		TPlayerController->GetPlayerViewPoint(TCamLoc, TCamRot);
		OutDirection = TCamRot.Vector();
	}
	// AI
	else if (Instigator)
	{
		//ADBShootAIController* AIController = MyPawn ? Cast<ADBShootAIController>(MyPawn->Controller) : NULL;
		//if (AIController != NULL)
		//{
		//	AimDirection = AIController->GetControlRotation().Vector();
		//}
		//else
		{
			OutDirection = Instigator->GetBaseAimRotation().Vector();
		}
	}

	return OutDirection;
}

void ADBCharacter::UpdateIronSightLoc(ADBWeaponBase* NewShootWeapon)
{
	ADBShootWeaponBase* TNewShootWeapon = Cast<ADBShootWeaponBase>(NewShootWeapon);
	const FVector SockLoc = TNewShootWeapon->GetMeshComp()->GetSocketTransform(FName(TEXT("IronSight")), RTS_Component).GetTranslation();
	m_IronSightLoc = NewShootWeapon->GetMeshComp()->GetRelativeTransform().InverseTransformPosition(SockLoc);
}

FORCEINLINE void ADBCharacter::PlayCameraShake(TSubclassOf<class UCameraShake> Shake, float Scale /*= 1.f*/, ECameraAnimPlaySpace::Type PlaySpace /*= ECameraAnimPlaySpace::CameraLocal*/, FRotator UserPlaySpaceRot /*= FRotator::ZeroRotator*/)
{
	if (Shake != nullptr)
	{
		ADBPlayerController* DBPlayerController = Cast<ADBPlayerController>(GetController());
		if (DBPlayerController)
		{
			DBPlayerController->ClientPlayCameraShake(Shake, Scale, PlaySpace, UserPlaySpaceRot);
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
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, COLLISION_INTERACTABLE, TraceParams);
    //DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f);
	//DrawDebugPoint(GetWorld(), Hit.Location, 10, FColor(255, 0, 255), false, 1.f);

	return Hit.GetActor();
}

//void ADBCharacter::CalcCamera(float DeltaTime, FMinimalViewInfo & OutResult)
//{
//	if (m_IsTargeting)
//	{
//
//		ADBShootWeaponBase* t = Cast<ADBShootWeaponBase>(m_HoldWeapon);
//
//		if (t)
//		{
//			t->m_AimCameraComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("head")));
//			t->m_AimCameraComp->GetCameraView(DeltaTime, OutResult);
//		}
//	}
//	else 
//	{
//		m_CameraComp->GetCameraView(DeltaTime, OutResult);
//	}
//}

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

void ADBCharacter::SetFPSCamera()
{
	m_CameraComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("head")));
	m_CameraComp->RelativeLocation = FVector(0, 10.f, 0);
	m_CurCameraMode = ECameraMode::E_FirstPersonPerspective;
}

void ADBCharacter::SetCameraAim(float Delta, bool bAim)
{
	if (m_CurCameraMode == ECameraMode::E_FirstPersonPerspective && m_HoldWeapon)
	{
		if (bAim)
		{
			//UpdateIronSightLoc(m_HoldWeapon);
			m_CameraComp->RelativeLocation = FMath::VInterpTo(m_CameraComp->RelativeLocation, m_IronSightLoc, Delta, 10.f);
		}
		else
		{
			m_CameraComp->RelativeLocation = FMath::VInterpTo(m_CameraComp->RelativeLocation, FVector(4.f, 5.f, -7.f), Delta, 10.f);
		}
	}
}




