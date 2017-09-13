// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "ZombieSurvivalGameState.h"

AZombieSurvivalGameState::AZombieSurvivalGameState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	m_fTimeScale(10.f),
	m_bIsNight(false),
	m_fSunsetTimeMark(17.f),
	m_fSunriseTimeMark(5.f),
	m_fTotalMinutesPerDay(24 * 60),
	m_iElapsedGameMinutes(0)
{

}

void AZombieSurvivalGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AZombieSurvivalGameState, m_iElapsedGameMinutes);
	DOREPLIFETIME(AZombieSurvivalGameState, m_bIsNight);
}

//------------------------- Шеее----------------------------//

void AZombieSurvivalGameState::SetTime(int32 time)
{
	m_iElapsedGameMinutes = time;
}

float AZombieSurvivalGameState::GetTimeOfDayIncrement()
{
	return (GetWorldSettings()->GetEffectiveTimeDilation() * m_fTimeScale);
}

bool AZombieSurvivalGameState::GetAndUpdateNightState()
{
	const float fTimeOfDay = m_iElapsedGameMinutes - GetElapsedDaysInMinutes();
	if (fTimeOfDay > m_fSunriseTimeMark * 60 && fTimeOfDay < m_fSunsetTimeMark * 60)
	{
		m_bIsNight = false;
	}
	else
	{
		m_bIsNight = true;
	}

	return m_bIsNight;
}

int32 AZombieSurvivalGameState::GetElapsedDays()
{
	const float fElapsedDays = m_iElapsedGameMinutes / m_fTotalMinutesPerDay;
	return FMath::FloorToInt(fElapsedDays);
}

int32 AZombieSurvivalGameState::GetElapsedDaysInMinutes()
{
	return m_fTotalMinutesPerDay * GetElapsedDays();
}

int32 AZombieSurvivalGameState::GetCurDayElapsedMinutes()
{
	return m_iElapsedGameMinutes - GetElapsedDaysInMinutes();
}

