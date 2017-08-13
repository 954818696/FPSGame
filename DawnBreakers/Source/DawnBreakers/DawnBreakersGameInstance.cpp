// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DawnBreakersGameInstance.h"
#include "GameModule/Level/LevelLoadAssist.h"
#include "GameModule/Event/EventSets.h"




void UDawnBreakersGameInstance::Init()
{
	Super::Init();

	DawnBreakerHelper::SaveGameInstance(this);

	m_LevelLoadAssisit = NewObject<ULevelLoadAssist>(this);

	if (!FParse::Param(FCommandLine::Get(), TEXT("server")))
	{
		FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UDawnBreakersGameInstance::BeginLoadMap);
		FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UDawnBreakersGameInstance::EndLoadMap);

	}

}

void UDawnBreakersGameInstance::Shutdown()
{
	Super::Shutdown();

	if (m_LevelLoadAssisit)
	{
		m_LevelLoadAssisit->Clear();
		m_LevelLoadAssisit->ConditionalBeginDestroy();
	}

	UEventSets::Clear();
}

void UDawnBreakersGameInstance::BeginLoadMap(const FString& MapName)
{
	if (!IsRunningDedicatedServer())
	{
		m_LevelLoadAssisit->OnLoadMasterLevelBegin(MapName);
	}
	
}

void UDawnBreakersGameInstance::EndLoadMap(UWorld* World)
{
	//if (!IsRunningDedicatedServer())
	{	
		m_LevelLoadAssisit->OnLoadMasterLevelFinish();

	}

	
}
