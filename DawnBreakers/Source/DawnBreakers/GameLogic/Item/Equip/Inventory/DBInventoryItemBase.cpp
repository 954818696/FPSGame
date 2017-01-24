// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBInventoryItemBase.h"

ADBInventoryItemBase::ADBInventoryItemBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	m_bForceAttachToOwner(false),
	m_EInventorySlot(EInventorySlot::InvisiblePack)
{
	PrimaryActorTick.bCanEverTick = false;

	m_SkeletalMeshComp = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("SkeletalMesh"));
	m_SkeletalMeshComp->SetCollisionObjectType(ECC_WorldDynamic);
	m_SkeletalMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	m_SkeletalMeshComp->SetSimulatePhysics(true);
	//m_SkeletalMeshComp->SetCollisionResponseToAllChannels(ECR_Block);
	RootComponent = m_SkeletalMeshComp;
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

		if (m_AttachSocketName.IsValid())
		{
			AttachToComponent(ItemOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, m_AttachSocketName);
		}
		else if (m_bForceAttachToOwner)
		{
			AttachToComponent(ItemOwner->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
		}
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

