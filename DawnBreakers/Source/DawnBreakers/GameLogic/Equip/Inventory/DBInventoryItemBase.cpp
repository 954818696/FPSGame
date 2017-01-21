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

