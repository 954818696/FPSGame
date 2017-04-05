// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ItemType.h"
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

	void PutFinal(class ADBInventoryItemBase* NetItem)
	{
		m_ItemsContainer.AddUnique(NetItem);
		++m_UsedSlotSize;
	}

	void RemoveOneFinal(ADBInventoryItemBase* RemovedItem)
	{
		int32  RemoveCount = m_ItemsContainer.Remove(RemovedItem);
		m_UsedSlotSize -= RemoveCount;
	}

	void RemoveAllFinal()
	{
		m_ItemsContainer.Empty();
		m_UsedSlotSize = 0;
	}

	TArray<ADBInventoryItemBase*> m_ItemsContainer;

	int32 m_UsedSlotSize;

	UPROPERTY(EditDefaultsOnly, Category = FInventorySlot)
	int32 m_SlotSize;

	UPROPERTY(EditDefaultsOnly, Category = FInventorySlot)
	EInventorySlot	m_SlotType;
};

USTRUCT(BlueprintType)
struct FAmmoSlot
{
	GENERATED_USTRUCT_BODY()

	FAmmoSlot() :
		m_MaxAmount(60),
		m_AmmoType(EAmmoType::RifleAmmo),
		m_CurrentAmount(0)
	{

	}

	UPROPERTY(EditDefaultsOnly, Category = FAmmoSlot)
	EAmmoType m_AmmoType;

	UPROPERTY(EditDefaultsOnly, Category = FAmmoSlot)
	int32 m_MaxAmount;

	UPROPERTY(EditDefaultsOnly, Category = FAmmoSlot)
	int32 m_CurrentAmount;
};


USTRUCT(BlueprintType)
struct FInventory
{
	GENERATED_USTRUCT_BODY()

	bool Put(ADBInventoryItemBase* NewItem);

	void RemoveOne(ADBInventoryItemBase* RemovedItem);

	void RemoveAllTypeSlot();

	void RemoveAllOneSlot(EInventorySlot RemoveSlotType);

	UPROPERTY(EditDefaultsOnly, Category = ADBInventoryBase)
	TArray<FInventorySlot> m_SlotsContainer;

	TArray<ADBInventoryItemBase*> m_CachedForSwitch;
};