// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DawnBreakersGameInstance.h"
#include "GameLogic/LogicGlue/LevelStreamLoader.h"




void UDawnBreakersGameInstance::Init()
{
	Super::Init();

	m_LevelStreamLoader = MakeShareable(new LevelStreamLoader());

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UDawnBreakersGameInstance::BeginLoadMap);
	FCoreUObjectDelegates::PostLoadMap.AddUObject(this, &UDawnBreakersGameInstance::EndLoadMap);
}

void UDawnBreakersGameInstance::Shutdown()
{
	Super::Shutdown();

	if (m_LevelStreamLoader.IsValid())
	{
		m_LevelStreamLoader->Clear();
		m_LevelStreamLoader.Reset();
	}

}

void UDawnBreakersGameInstance::BeginLoadMap(const FString& MapName)
{

}

void UDawnBreakersGameInstance::EndLoadMap()
{

}
