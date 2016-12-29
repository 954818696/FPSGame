// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBInventoryItemBase.h"


// Sets default values
ADBInventoryItemBase::ADBInventoryItemBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ADBInventoryItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADBInventoryItemBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

