// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DShooterWeaponBase.h"


// Sets default values
ADShooterWeaponBase::ADShooterWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADShooterWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADShooterWeaponBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

