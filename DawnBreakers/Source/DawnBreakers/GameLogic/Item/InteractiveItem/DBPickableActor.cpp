// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBPickableActor.h"


// Sets default values
ADBPickableActor::ADBPickableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ADBPickableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADBPickableActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

