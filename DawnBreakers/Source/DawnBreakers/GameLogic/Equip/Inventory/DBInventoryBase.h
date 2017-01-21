// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DBInventoryItemBase.h"
#include "DBInventoryBase.generated.h"

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_USTRUCT_BODY()

		FInventorySlot() :
		m_SlotSize(1),
		m_SlotType(EInventorySlot::InvisiblePack)
	{

	}
	UPROPERTY(EditDefaultsOnly, Category = FInventorySlot)
	int32 m_SlotSize;

	UPROPERTY(EditDefaultsOnly, Category = FInventorySlot)
	EInventorySlot	m_SlotType;
};

// Inventory Visualize in the future.
UCLASS(Abstract)
class DAWNBREAKERS_API ADBInventoryBase : public AActor
{
	GENERATED_UCLASS_BODY()
	
public:	
	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;

	bool AddToInventory(class ADBInventoryItemBase* NewEquipment);

	void RemoveFromInventory(ADBInventoryItemBase* NewEquipment);

	ADBInventoryItemBase* GetOneItemByItemSequence(const ADBInventoryItemBase* FindBaseItem, bool bNext);

protected:
	UPROPERTY(EditDefaultsOnly, Category = ADBInventoryBase)
	TArray<FInventorySlot> m_ItemContainer;

private:
	TArray<ADBInventoryItemBase*> m_ItemsContainer;
	
};
