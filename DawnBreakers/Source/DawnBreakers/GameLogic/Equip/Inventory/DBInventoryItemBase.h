// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GameLogic/Character/DBCharacter.h"
#include "ItemType.h"
#include "DBInventoryItemBase.generated.h"



UCLASS(Blueprintable, Abstract, NotPlaceable)
class DAWNBREAKERS_API ADBInventoryItemBase : public AActor
{
	GENERATED_UCLASS_BODY()
	
public:	

	virtual void BeginPlay() override;

	ADBCharacter* GetItemOwner() const 
	{
		return m_OwnerCharacter;
	}

	void SetItemOwner(ADBCharacter* ItemOwner);

	EInventorySlot GetStorageSlotType() const
	{
		return m_EInventorySlot;
	}
	
protected:
	UPROPERTY(VisibleAnywhere, Category = ADBInventoryItemBase)
	EInventorySlot m_EInventorySlot;

	UPROPERTY(VisibleAnywhere, Category = ADBInventoryItemBase)
	FName m_AttachSocketName;

	UPROPERTY(VisibleAnywhere, Category = ADBInventoryItemBase)
	bool m_bForceAttachToOwner;

	ADBCharacter* m_OwnerCharacter;
	
};
