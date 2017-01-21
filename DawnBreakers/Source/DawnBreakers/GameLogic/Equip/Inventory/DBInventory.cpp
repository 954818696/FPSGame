// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBInventory.h"
#include "DBInventoryItemBase.h"


ADBInventory::ADBInventory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADBInventory::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADBInventory::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ADBInventory::AddToInventory(ADBInventoryItemBase* NewEquipment)
{
	if (NewEquipment && NewEquipment->IsValidLowLevel())
	{
		m_ItemsContainer.AddUnique(NewEquipment);
	}
}

void ADBInventory::RemoveFromInventory(ADBInventoryItemBase* NewEquipment)
{
	if (NewEquipment && NewEquipment->IsValidLowLevel())
	{
		m_ItemsContainer.RemoveSwap(NewEquipment);
	}
}

