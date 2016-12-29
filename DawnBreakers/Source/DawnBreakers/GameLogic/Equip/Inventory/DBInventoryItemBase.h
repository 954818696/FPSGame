// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GameLogic/Character/DBCharacter.h"
#include "DBInventoryItemBase.generated.h"

UCLASS(Blueprintable, Abstract, NotPlaceable)
class DAWNBREAKERS_API ADBInventoryItemBase : public AActor
{
	GENERATED_UCLASS_BODY()
	
public:	


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	ADBCharacter* GetOwner() const 
	{
		return m_OwnerCharacter;
	}
	
protected:
	ADBCharacter* m_OwnerCharacter;
	
};
