// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "LevelAssist.h"

LevelAssist::LevelAssist()
{
}

LevelAssist::~LevelAssist()
{
}

void LevelAssist::OpenStoryModeLevel(const FName& SubLevelName)
{
	UWorld* TGameWorld = DawnBreakerHelper::GetGameWorld();

	UGameplayStatics::OpenLevel(TGameWorld, SubLevelName);
}

void LevelAssist::OpenMultiplayerLevel(const FName& LevelName)
{

}

void LevelAssist::Clear()
{

}
