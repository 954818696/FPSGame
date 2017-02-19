// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GameLogic/Item/ItemInteractInterface.h"
#include "GameLogic/Character/DBCharacter.h"
#include "ItemType.h"
#include "DBInventoryItemBase.generated.h"

UCLASS(Blueprintable, Abstract, NotPlaceable)
class DAWNBREAKERS_API ADBInventoryItemBase : public AActor, public IItemInteractInterface
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

	virtual void SetInteractFocus() override;

	virtual void LoseInteractFocus() override;

	void AttachToTarget(EItemAttachToTargetType TargetType);

	bool IsNeedAttachToTarget() const { return m_AttachToTargetConfigs.Num() > 0; }

	void ConfigAttachToTargetSceneComponent(USceneComponent* AttachToTargetSceneComponent);

protected:
	UPROPERTY(EditAnywhere, Category = ADBInventoryItemBase)
	USkeletalMeshComponent* m_SkeletalMeshComp;

	UPROPERTY(EditAnywhere, Category = ADBInventoryItemBase)
	EInventorySlot m_EInventorySlot;

	UPROPERTY(EditAnywhere, Category = ADBInventoryItemBase)
	TArray<FItemAttachToTargetSocket> m_AttachToTargetConfigs;
};
