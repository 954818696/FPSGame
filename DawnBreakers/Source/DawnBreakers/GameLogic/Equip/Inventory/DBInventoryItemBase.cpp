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

	//m_StaticMeshComp = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("StaticMesh"));
	//m_StaticMeshComp->SetCollisionObjectType(ECC_WorldDynamic);
	//m_StaticMeshComp->SetSimulatePhysics(true);
	//m_StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//m_StaticMeshComp->SetVisibility(true);
	////m_StaticMeshComp->SetupAttachment(m_SceneComponentRoot);
	//RootComponent = m_StaticMeshComp;
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
	m_MeshComp->SetRenderCustomDepth(true);
}

void ADBInventoryItemBase::LoseInteractFocus()
{
	m_MeshComp->SetRenderCustomDepth(false);
}

