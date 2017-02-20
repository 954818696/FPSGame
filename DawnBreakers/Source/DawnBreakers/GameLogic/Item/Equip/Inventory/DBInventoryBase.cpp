// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBInventoryBase.h"


ADBInventoryBase::ADBInventoryBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

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
	bool Result = false;
	if (NewEquipment && NewEquipment->IsValidLowLevel())
	{
		EInventorySlot SlotType = NewEquipment->GetStorageSlotType();
		Result = m_Inventory.Put(NewEquipment);
		if (Result)
		{
			ADBCharacter* TOwner = Cast<ADBCharacter>(GetOwner());
			if (TOwner)
			{
				SetItemOwner(TOwner);
			}
		}
	}

	return Result;
}

void ADBInventoryBase::RemoveFromInventory(ADBInventoryItemBase* RemovedEquipment)
{
	if (RemovedEquipment && RemovedEquipment->IsValidLowLevel())
	{
		m_Inventory.RemoveOne(RemovedEquipment);
	}
}

ADBInventoryItemBase* ADBInventoryBase::GetOneItemByItemSequence(const ADBInventoryItemBase* FindBaseItem, bool bNext)
{
	ADBInventoryItemBase* ReturnItem = nullptr;
 
	const TArray<ADBInventoryItemBase*> &ItemsContainer = m_Inventory.m_CachedForSwitch;
	const int32 ItemCount = ItemsContainer.Num();
	if (ItemCount > 1)
	{
		const int32 CurrentItemIndex = ItemsContainer.IndexOfByKey(FindBaseItem);
		if (CurrentItemIndex != INDEX_NONE)
		{
			if (bNext)
			{
				ReturnItem = ItemsContainer[(CurrentItemIndex + 1) % ItemCount];
			}
			else
			{
				ReturnItem = ItemsContainer[(ItemCount + CurrentItemIndex - 1) % ItemCount];
			}
		}
	}

	return ReturnItem;
}

