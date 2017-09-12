// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ZombieSurvivalHUD.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API AZombieSurvivalHUD : public AHUD
{
	GENERATED_BODY()
	
	
public:


	UFUNCTION(BlueprintImplementableEvent, Category = "HUDEvents")
	void HandleMsg(const FString& Msg);
	
};
