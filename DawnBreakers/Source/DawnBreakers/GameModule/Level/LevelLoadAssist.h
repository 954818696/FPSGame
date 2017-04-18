// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "LevelLoadAssist.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API ULevelLoadAssist : public UObject
{
	GENERATED_BODY()
	
public:
	void OnLoadMasterLevelBegin(const FString& MapName);

	void OnLoadMasterLevelFinish();

	void OpenStoryModeLevel(const FName& PersistLevelName);

	void OpenMultiplayerLevel(const FName& LevelName);

	void Clear();

private:
	void UpdateLoadProgress();

	UFUNCTION()
	void LoadSubLevelFinish();

private:
	FName m_LoadMapName;

	FTimerHandle TimerHandle_UpdateLoadProgress;
	
};
