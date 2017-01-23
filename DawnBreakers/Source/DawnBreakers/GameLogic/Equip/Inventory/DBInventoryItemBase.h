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
		return Cast<ADBCharacter>(GetOwner());
	}

	void SetItemOwner(ADBCharacter* ItemOwner);

	EInventorySlot GetStorageSlotType() const
	{
		return m_EInventorySlot;
	}

	virtual void SetInteractFocus();

	virtual void LoseInteractFocus();

protected:
	UPROPERTY(EditAnywhere, Category = "ADBInventoryItemBase")
	UMeshComponent* m_MeshComp;

	UPROPERTY(EditAnywhere, Category = ADBInventoryItemBase)
	EInventorySlot m_EInventorySlot;

	UPROPERTY(EditAnywhere, Category = ADBInventoryItemBase)
	FName m_AttachSocketName;

	UPROPERTY(EditAnywhere, Category = ADBInventoryItemBase)
	bool m_bForceAttachToOwner;
};
