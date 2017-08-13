// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DBBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API UDBBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "UDBBlueprintFunctionLibrary")
	static class UEventSets* GetEventSets();
	
	
};
