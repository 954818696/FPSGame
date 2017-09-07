// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "EventSets.h"


UEventSets* UEventSets::m_EventSetsInstance = nullptr;

UEventSets* UEventSets::Instance()
{
	if (m_EventSetsInstance == nullptr || ! m_EventSetsInstance->IsValidLowLevel())
	{
		m_EventSetsInstance = NewObject<UEventSets>(DawnBreakerHelper::GetGameWorld());
		m_EventSetsInstance->AddToRoot();
	}

	return m_EventSetsInstance;
}

void UEventSets::Clear()
{
	if (m_EventSetsInstance)
	{
		m_EventSetsInstance->RemoveFromRoot();
		m_EventSetsInstance = nullptr;
	}
}

void UEventSets::ClearAllBind()
{
	OnSendLevelEvent.Clear();
	OnLevelStreamLoadPercent.Clear();
	OnPreparedForGetInGame.Clear();
	OnRestartPlayer.Clear();
}
