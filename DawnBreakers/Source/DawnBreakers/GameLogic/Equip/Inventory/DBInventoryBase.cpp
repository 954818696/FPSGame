// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBInventoryBase.h"


ADBInventoryBase::ADBInventoryBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADBInventoryBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADBInventoryBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

bool ADBInventoryBase::AddToInventory(ADBInventoryItemBase* NewEquipment)
{
	if (NewEquipment && NewEquipment->IsValidLowLevel())
	{
		m_ItemsContainer.AddUnique(NewEquipment);
	}

	return true;
}

void ADBInventoryBase::RemoveFromInventory(ADBInventoryItemBase* NewEquipment)
{
	if (NewEquipment && NewEquipment->IsValidLowLevel())
	{
		m_ItemsContainer.Remove(NewEquipment);
	}
}

ADBInventoryItemBase* ADBInventoryBase::GetOneItemByItemSequence(const ADBInventoryItemBase* FindBaseItem, bool bNext)
{

	ADBInventoryItemBase* ReturnItem = nullptr;
	if (m_ItemsContainer.Num() > 1)
	{
		const int32 CurrentItemIndex = m_ItemsContainer.IndexOfByKey(FindBaseItem);
		if (CurrentItemIndex != INDEX_NONE)
		{
			const int32 ItemCount = m_ItemsContainer.Num();
			if (bNext)
			{
				ReturnItem = m_ItemsContainer[(CurrentItemIndex + 1) % ItemCount];
			}
			else
			{
				ReturnItem = m_ItemsContainer[(ItemCount + CurrentItemIndex - 1) % ItemCount];
			}
		}
	}

	return ReturnItem;
}

