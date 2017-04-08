// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/CheatManager.h"
#include "DBCheatManager.generated.h"

/**
 * 
 */
UCLASS(Within = DBBasePlayerController)
class DAWNBREAKERS_API UDBCheatManager : public UCheatManager
{
	GENERATED_BODY()

	UFUNCTION(exec)
	virtual void Test();
	
	
};
