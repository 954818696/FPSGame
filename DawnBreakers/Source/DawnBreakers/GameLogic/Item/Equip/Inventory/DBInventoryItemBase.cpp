// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBInventoryItemBase.h"

ADBInventoryItemBase::ADBInventoryItemBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	m_bForceAttachToOwner(false),
	m_EInventorySlot(EInventorySlot::InvisiblePack)
{
	PrimaryActorTick.bCanEverTick = true;

	m_SkeletalMeshComp = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("SkeletalMesh"));
	RootComponent = m_SkeletalMeshComp;
	//m_SkeletalMeshComp->SetCollisionObjectType(ECC_WorldDynamic);
	//m_SkeletalMeshComp->SetCollisionResponseToAllChannels(ECR_Block);
	m_SkeletalMeshComp->SetCollisionProfileName(FName(TEXT("PhysicsActor")));
	m_SkeletalMeshComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	m_SkeletalMeshComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	m_SkeletalMeshComp->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
	m_SkeletalMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	m_SkeletalMeshComp->SetSimulatePhysics(true);
	m_SkeletalMeshComp->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	m_SkeletalMeshComp->bEnablePhysicsOnDedicatedServer = true;
	bReplicates = true;
	bAlwaysRelevant = true;


}

void ADBInventoryItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADBInventoryItemBase::SetItemOwner(ADBCharacter* ItemOwner)
{
	if (ItemOwner && ItemOwner->IsValidLowLevel())
	{
		SetOwner(ItemOwner);
		Instigator = ItemOwner;

		//if (m_AttachSocketName.IsValid())
		//{
		//	AttachToComponent(ItemOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, m_AttachSocketName);
		//}
		//else if (m_bForceAttachToOwner)
		//{
		//	AttachToComponent(ItemOwner->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
		//}
	}
}

void ADBInventoryItemBase::SetInteractFocus()
{
	m_SkeletalMeshComp->SetRenderCustomDepth(true);
}

void ADBInventoryItemBase::LoseInteractFocus()
{
	m_SkeletalMeshComp->SetRenderCustomDepth(false);
}

