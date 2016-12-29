// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBBulletProjectileBase.h"


// Sets default values
ADBBulletProjectileBase::ADBBulletProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADBBulletProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADBBulletProjectileBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

