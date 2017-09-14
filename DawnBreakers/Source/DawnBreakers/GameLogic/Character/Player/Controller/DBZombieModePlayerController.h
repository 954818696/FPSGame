// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameLogic/Character/Player/Controller/DBPlayerController.h"
#include "DBZombieModePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ADBZombieModePlayerController : public ADBPlayerController
{
	GENERATED_UCLASS_BODY()
	
public:
	UFUNCTION(Reliable, Client)
	void SendHUDMsg(const FString& Msg);

	UFUNCTION(BlueprintCallable, Category = ADBZombieModePlayerController)
	void SetHUDVisible(bool bShow);
	
};
