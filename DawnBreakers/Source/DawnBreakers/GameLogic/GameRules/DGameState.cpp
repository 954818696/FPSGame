// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DGameState.h"

ADGameState::ADGameState()
	:Super()
{
	mfTimeScale = 10.f;
	mbIsNight = false;
	mfSunsetTimeMark = 17.f;
	mfSunriseTimeMark = 5.f;
	mfTotalMinutesPerDay = 24 * 60;
}

void ADGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADGameState, miElapsedGameMinutes);
	DOREPLIFETIME(ADGameState, mbIsNight);
}

//------------------------- Шеее----------------------------//

void ADGameState::SetTime(float time)
{
	miElapsedGameMinutes = time;
}

float ADGameState::GetTimeOfDayIncrement()
{
	return (GetWorldSettings()->GetEffectiveTimeDilation() * mfTimeScale);
}

bool ADGameState::GetAndUpdateNightState()
{
	const float fTimeOfDay = miElapsedGameMinutes - GetElapsedDaysInMinutes();
	if (fTimeOfDay > mfSunriseTimeMark * 60 && fTimeOfDay < mfSunsetTimeMark * 60)
	{
		mbIsNight = false;
	}
	else
	{
		mbIsNight = true;
	}

	return mbIsNight;
}

int32 ADGameState::GetElapsedDays()
{
	const float fElapsedDays = miElapsedGameMinutes / mfTotalMinutesPerDay;
	return FMath::FloorToInt(fElapsedDays);
}

int32 ADGameState::GetElapsedDaysInMinutes()
{
	return mfTotalMinutesPerDay * GetElapsedDays();
}

int32 ADGameState::GetCurDayElapsedMinutes()
{
	return miElapsedGameMinutes - GetElapsedDaysInMinutes();
}


