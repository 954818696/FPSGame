// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DawnBreakersGameInstance.h"
#include "GameModule/Level/LevelLoadAssist.h"




void UDawnBreakersGameInstance::Init()
{
	Super::Init();

	DawnBreakerHelper::SaveGameInstance(this);

	m_LevelLoadAssisit = NewObject<ULevelLoadAssist>(this);

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UDawnBreakersGameInstance::BeginLoadMap);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UDawnBreakersGameInstance::EndLoadMap);
}

void UDawnBreakersGameInstance::Shutdown()
{
	Super::Shutdown();

	if (m_LevelLoadAssisit)
	{
		m_LevelLoadAssisit->Clear();
		m_LevelLoadAssisit->ConditionalBeginDestroy();
	}

}

void UDawnBreakersGameInstance::BeginLoadMap(const FString& MapName)
{
	m_LevelLoadAssisit->OnLoadMasterLevelBegin(MapName);
}

void UDawnBreakersGameInstance::EndLoadMap(UWorld* World)
{
	m_LevelLoadAssisit->OnLoadMasterLevelFinish();
}
