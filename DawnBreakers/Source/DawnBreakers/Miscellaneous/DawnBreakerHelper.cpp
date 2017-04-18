// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DawnBreakerHelper.h"

UGameInstance* DawnBreakerHelper::m_GameIntance = nullptr;

DawnBreakerHelper::DawnBreakerHelper()
{
}

DawnBreakerHelper::~DawnBreakerHelper()
{
}

UWorld* DawnBreakerHelper::GetGameWorld()
{
	if (m_GameIntance)
	{
		return m_GameIntance->GetWorld();
	}

	return nullptr;
}

void DawnBreakerHelper::SaveGameInstance(UGameInstance* NewGameInstance)
{
	m_GameIntance = NewGameInstance;
}
