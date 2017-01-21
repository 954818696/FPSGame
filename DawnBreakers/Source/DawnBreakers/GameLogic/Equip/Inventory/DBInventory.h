// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DBInventory.generated.h"


// Inventory Visualize in the future.
UCLASS()
class DAWNBREAKERS_API ADBInventory : public AActor
{
	GENERATED_UCLASS_BODY()
	
public:	
	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;

	void AddToInventory(class ADBInventoryItemBase* NewEquipment);

	void RemoveFromInventory(ADBInventoryItemBase* NewEquipment);

private:
	TArray<ADBInventoryItemBase*> m_ItemsContainer;
	
};
