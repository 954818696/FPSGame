// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "InventoryStruct.h"

bool FInventory::Put(ADBInventoryItemBase* NewItem)
{
	bool Result = false;

	EInventorySlot SlotType = NewItem->GetStorageSlotType();
	for (int32 i = 0; i < m_SlotsContainer.Num(); ++i)
	{
		if (SlotType == m_SlotsContainer[i].m_SlotType)
		{
			if (m_SlotsContainer[i].IsCanPutIn())
			{
				m_SlotsContainer[i].PutFinal(NewItem);
				Result = true;
				DAWNBREAKERS_LOG_INFO("Put %s in slot %s", *NewItem->GetName(), *GETENUMSTRING("EInventorySlot", m_SlotsContainer[i].m_SlotType));
				if (SlotType == EInventorySlot::BackPack || SlotType == EInventorySlot::WaistPack)
				{
					m_CachedForSwitch.AddUnique(NewItem);
				}
			}
			else 
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Put Failed Pack full!");
				DAWNBREAKERS_LOG_WARNING("Put %s failed %s slot full", *NewItem->GetName(), *GETENUMSTRING("EInventorySlot", m_SlotsContainer[i].m_SlotType));
			}
			break;
		}
	}

	return Result;
}

void FInventory::RemoveOne(ADBInventoryItemBase* RemovedItem)
{
	EInventorySlot SlotType = RemovedItem->GetStorageSlotType();
	for (int32 i = 0; i < m_SlotsContainer.Num(); ++i)
	{	
		if (SlotType  == m_SlotsContainer[i].m_SlotType)
		{
			m_SlotsContainer[i].RemoveOneFinal(RemovedItem);
			if (SlotType == EInventorySlot::BackPack || SlotType == EInventorySlot::WaistPack)
			{
				m_CachedForSwitch.Remove(RemovedItem);
			}
			break;
		}
	}
}

void FInventory::RemoveAllTypeSlot()
{
	for (int32 i = 0; i < m_SlotsContainer.Num(); ++i)
	{
		m_SlotsContainer[i].RemoveAllFinal();
		m_CachedForSwitch.Empty();
	}
}

void FInventory::RemoveAllOneSlot(EInventorySlot RemoveSlotType)
{
	for (int32 i = 0; i < m_SlotsContainer.Num(); ++i)
	{
		if (RemoveSlotType == m_SlotsContainer[i].m_SlotType)
		{
			if (RemoveSlotType == EInventorySlot::BackPack || RemoveSlotType == EInventorySlot::WaistPack)
			{
				for (int32 j = 0; j < m_SlotsContainer[i].m_ItemsContainer.Num(); ++j)
				{
					m_CachedForSwitch.Remove(m_SlotsContainer[i].m_ItemsContainer[j]);
				}
			}
			m_SlotsContainer[i].RemoveAllFinal();
			break;
		}
	}
}
