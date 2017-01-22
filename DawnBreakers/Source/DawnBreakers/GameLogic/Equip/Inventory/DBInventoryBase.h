// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "InventoryStruct.h"
#include "DBInventoryBase.generated.h"

class ADBInventoryItemBase;



// Inventory Visualize in the future.
UCLASS(Abstract)
class DAWNBREAKERS_API ADBInventoryBase : public AActor
{
	GENERATED_UCLASS_BODY()
	
public:	
	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;

	bool AddToInventory(class ADBInventoryItemBase* NewEquipment);

	void RemoveFromInventory(ADBInventoryItemBase* RemovedEquipment);

	ADBInventoryItemBase* GetOneItemByItemSequence(const ADBInventoryItemBase* FindBaseItem, bool bNext);

protected:
	UPROPERTY(EditDefaultsOnly, Category = ADBInventoryBase)
	FInventory m_Inventory;
};
