// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "EventSets.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSendLevelEvent, UObject*, HostObject, int32, EventId);

UCLASS()
class DAWNBREAKERS_API UEventSets : public UObject
{
	GENERATED_BODY()
	
public:
	static  UEventSets* Instance();

	static void Clear();
	
public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "DBEventSets")
	FOnSendLevelEvent OnSendLevelEvent;

private:
	static UEventSets* m_EventSetsInstance;
	
};
