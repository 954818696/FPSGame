// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ZombieSurvivalPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API AZombieSurvivalPlayerState : public APlayerState
{
	GENERATED_UCLASS_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = AZombieSurvivalPlayerState)
	int32 Death = 0;

	UPROPERTY(BlueprintReadOnly, Category = AZombieSurvivalPlayerState)
	int32 Killed = 0;
};
