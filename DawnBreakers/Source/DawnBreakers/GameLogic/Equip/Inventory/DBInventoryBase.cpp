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
	bool result = false;
	//if (NewEquipment && NewEquipment->IsValidLowLevel())
	//{
	//	EInventorySlot SlotType = NewEquipment->GetStorageSlotType();

	//	for (int32 i = 0; i < m_SlotsContainer.Num(); ++i)
	//	{
	//		if (m_SlotsContainer[i].m_SlotType == SlotType && m_SlotsContainer[i].IsCanPutIn())
	//		{
	//			result = true;
	//			m_SlotsContainer[i].Put(NewEquipment);
	//		}
	//	}
	//}

	return result;
}

void ADBInventoryBase::RemoveFromInventory(ADBInventoryItemBase* RemovedEquipment)
{
	if (RemovedEquipment && RemovedEquipment->IsValidLowLevel())
	{
		//EInventorySlot SlotType = RemovedEquipment->GetStorageSlotType();
		//for (int32 i = 0; i < m_SlotsContainer.Num(); ++i)
		//{
		//	if (m_SlotsContainer[i].m_SlotType == SlotType)
		//	{
		//		m_SlotsContainer[i].RemoveOne(RemovedEquipment);
		//	}
		//}
	}
}

ADBInventoryItemBase* ADBInventoryBase::GetOneItemByItemSequence(const ADBInventoryItemBase* FindBaseItem, bool bNext)
{

	ADBInventoryItemBase* ReturnItem = nullptr;
	//if (m_SlotsContainer.Num() > 1)
	//{
	//	const int32 CurrentItemIndex = m_ItemsContainer.IndexOfByKey(FindBaseItem);
	//	if (CurrentItemIndex != INDEX_NONE)
	//	{
	//		const int32 ItemCount = m_ItemsContainer.Num();
	//		if (bNext)
	//		{
	//			ReturnItem = m_ItemsContainer[(CurrentItemIndex + 1) % ItemCount];
	//		}
	//		else
	//		{
	//			ReturnItem = m_ItemsContainer[(ItemCount + CurrentItemIndex - 1) % ItemCount];
	//		}
	//	}
	//}

	return ReturnItem;
}

