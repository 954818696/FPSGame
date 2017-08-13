// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "EventSets.generated.h"

/**
 * 
 */
namespace EventNameSets
{
	const FString EventPreparedForGettingIn = TEXT("PreparedForGettingIn");
}

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSendLevelEvent, UObject*, HostObject, FString, EventName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelStreamLoadPercent, float, Percent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPreparedForGetInGame);

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

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "DBEventSets")
	FOnLevelStreamLoadPercent OnLevelStreamLoadPercent;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "DBEventSets")
	FOnPreparedForGetInGame OnPreparedForGetInGame;

private:
	static UEventSets* m_EventSetsInstance;
	
};
