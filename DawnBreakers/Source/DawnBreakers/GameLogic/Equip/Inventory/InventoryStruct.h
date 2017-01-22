// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DBInventoryItemBase.h"
#include "InventoryStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_USTRUCT_BODY()

		FInventorySlot() :
		m_SlotSize(1),
		m_SlotType(EInventorySlot::InvisiblePack),
		m_UsedSlotSize(0)
	{

	}

	bool IsCanPutIn() const { return m_UsedSlotSize < m_SlotSize; }

	void Put(class ADBInventoryItemBase* NetItem)
	{

	}

	void RemoveOne(ADBInventoryItemBase* RemovedItem)
	{
		m_ItemsContainer.Remove(RemovedItem);
	}

	void RemoveAll()
	{
		m_ItemsContainer.Empty();
	}

	TArray<ADBInventoryItemBase*> m_ItemsContainer;

	int32 m_UsedSlotSize;

	UPROPERTY(EditDefaultsOnly, Category = FInventorySlot)
		int32 m_SlotSize;

	UPROPERTY(EditDefaultsOnly, Category = FInventorySlot)
		EInventorySlot	m_SlotType;
};

USTRUCT(BlueprintType)
struct FInventory
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, Category = ADBInventoryBase)
		TArray<FInventorySlot> m_SlotsContainer;

	TArray<ADBInventoryItemBase*> m_AllCached;

	bool Put(ADBInventoryItemBase* NewItem)
	{
		//for (int32 i = 0; i < m_SlotsContainer.Num(); ++i)
		//{

		//}
		//m_ItemsContainer.AddUnique(NetItem);
		//++m_UsedSlotSize;
	}

	void RemoveOne(ADBInventoryItemBase* RemovedItem)
	{

	}

	void RemoveAll()
	{

	}
};