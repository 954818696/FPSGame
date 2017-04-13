// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DawnBreakersGameInstance.h"
#include "GameModule/Level/LevelAssist.h"




void UDawnBreakersGameInstance::Init()
{
	Super::Init();

	m_LevelAssist = MakeShareable(new LevelAssist());

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UDawnBreakersGameInstance::BeginLoadMap);
	FCoreUObjectDelegates::PostLoadMap.AddUObject(this, &UDawnBreakersGameInstance::EndLoadMap);
}

void UDawnBreakersGameInstance::Shutdown()
{
	Super::Shutdown();

	if (m_LevelAssist.IsValid())
	{
		m_LevelAssist->Clear();
		m_LevelAssist.Reset();
	}

}

void UDawnBreakersGameInstance::BeginLoadMap(const FString& MapName)
{

}

void UDawnBreakersGameInstance::EndLoadMap()
{

}
