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
				NewEquipment->SetItemOwner(TOwner);
			}
		}
	}

	return Result;
}

void ADBInventoryBase::RemoveFromInventory(ADBInventoryItemBase* RemovedEquipment, bool bDrop)
{
	if (RemovedEquipment && RemovedEquipment->IsValidLowLevel())
	{
		m_Inventory.RemoveOne(RemovedEquipment);
	}

	if (bDrop)
	{
		DropItem(RemovedEquipment);
	}
}

void ADBInventoryBase::RemoveAllFromInventory(bool bDrop)
{
	TArray<ADBInventoryItemBase *> OutDroppedItems;
	m_Inventory.GetAllItems(OutDroppedItems);
	m_Inventory.RemoveAllTypeSlot();

	if (!bDrop)
	{
		for (int32 i = 0; i < OutDroppedItems.Num(); ++i)
		{
			OutDroppedItems[i]->Destroy();
		}
	}
	else
	{
		for (int32 i = 0; i < OutDroppedItems.Num(); ++i)
		{
			DropItem(OutDroppedItems[i]);
		}
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

bool ADBInventoryBase::IsHaveAmmo(EAmmoType AmmoType) const
{
	for (int32 i = 0; i < m_Ammo.Num(); ++i)
	{
		if (m_Ammo[i].m_AmmoType == AmmoType)
		{
			return m_Ammo[i].m_CurrentAmount > 0;
		}
	}

	return false;
}

int32 ADBInventoryBase::GetAmmoForWeapon(EAmmoType AmmoType, int32 AmmoClipSize, int32 CurAmmosInClip)
{
	int32 GetAmmos = 0;
	for (int32 i = 0; i < m_Ammo.Num(); ++i)
	{
		if (m_Ammo[i].m_AmmoType == AmmoType)
		{
			int32 NeedAmmos = AmmoClipSize - CurAmmosInClip;
			if (m_Ammo[i].m_CurrentAmount >= NeedAmmos)
			{
				GetAmmos = NeedAmmos;
				m_Ammo[i].m_CurrentAmount -= NeedAmmos;
			}
			else
			{
				GetAmmos = m_Ammo[i].m_CurrentAmount;
				m_Ammo[i].m_CurrentAmount = 0;
			}
			break;
		}
	}

	return GetAmmos;
}

int32 ADBInventoryBase::GetTotalAmmoForWeapon(EAmmoType AmmoType)
{
	for (int32 i = 0; i < m_Ammo.Num(); ++i)
	{
		if (m_Ammo[i].m_AmmoType == AmmoType)
		{
			return m_Ammo[i].m_CurrentAmount;
		}
	}

	return 0;
}

void ADBInventoryBase::DropItem(ADBInventoryItemBase* Item)
{
	
}

