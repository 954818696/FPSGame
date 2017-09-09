// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "InventoryStruct.h"
#include "DBInventoryBase.generated.h"

// This Inventory means all things  equiped on the body.

UCLASS(Abstract)
class DAWNBREAKERS_API ADBInventoryBase : public ADBInventoryItemBase
{
	GENERATED_UCLASS_BODY()
	
public:	
	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;

	bool AddToInventory(class ADBInventoryItemBase* NewEquipment);

	void RemoveFromInventory(ADBInventoryItemBase* RemovedEquipment, bool bDrop);

	// If bDrop false, directly destroy all items.
	void RemoveAllFromInventory(bool bDrop);

	ADBInventoryItemBase* GetOneItemByItemSequence(const ADBInventoryItemBase* FindBaseItem, bool bNext);

	ADBInventoryItemBase* GetOneSwitchableItem(int32 index);

	bool AddAmmo() { return true; }

	bool IsHaveAmmo(EAmmoType AmmoType) const;

	int32 GetAmmoForWeapon(EAmmoType AmmoType, int32 AmmoClipSize, int32 CurAmmosInClip);

	int32 GetTotalAmmoForWeapon(EAmmoType AmmoType);

private:
	void DropItem(ADBInventoryItemBase* Item);

protected:
	UPROPERTY(EditDefaultsOnly, Category = ADBInventoryBase)
	FInventory m_Inventory;

	UPROPERTY(EditDefaultsOnly, Category = ADBInventoryBase)
	TArray<FAmmoSlot> m_Ammo;

	// Mesh.

private:

	FAmmoSlot* m_CurrentUsedAmmo;
};
