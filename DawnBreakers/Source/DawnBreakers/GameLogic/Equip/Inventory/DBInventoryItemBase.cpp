// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBInventoryItemBase.h"


// Sets default values
ADBInventoryItemBase::ADBInventoryItemBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	m_bForceAttachToOwner(false),
	m_EInventorySlot(EInventorySlot::InvisiblePack)
{
	PrimaryActorTick.bCanEverTick = false;

	m_StaticMeshComp = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("StaticMesh"));
	m_StaticMeshComp->SetCollisionObjectType(ECC_WorldDynamic);
	//m_StaticMeshComp->SetSimulatePhysics(true);
	//m_StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	m_StaticMeshComp->SetVisibility(false);
	m_StaticMeshComp->SetupAttachment(GetRootComponent());
}

void ADBInventoryItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADBInventoryItemBase::SetItemOwner(ADBCharacter* ItemOwner)
{
	if (ItemOwner && ItemOwner->IsValidLowLevel())
	{
		m_OwnerCharacter = ItemOwner;

		if (m_AttachSocketName.IsValid())
		{
			AttachToComponent(m_OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, m_AttachSocketName);
		}
		else if (m_bForceAttachToOwner)
		{
			AttachToComponent(m_OwnerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
		}
	}
}

void ADBInventoryItemBase::SetInteractFocus()
{
	m_StaticMeshComp->SetRenderCustomDepth(true);
}

void ADBInventoryItemBase::LoseInteractFocus()
{
	m_StaticMeshComp->SetRenderCustomDepth(false);
}

