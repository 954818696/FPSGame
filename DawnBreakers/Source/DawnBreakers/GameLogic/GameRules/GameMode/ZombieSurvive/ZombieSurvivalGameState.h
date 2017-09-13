// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "ZombieSurvivalGameState.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API AZombieSurvivalGameState : public AGameState
{
	GENERATED_UCLASS_BODY()
	
public:
	// 日照系统
	// 每个Tick增加时间
	float GetTimeOfDayIncrement();

	// 判断日间状态和更新状态
	bool GetAndUpdateNightState();

	bool IsNight();

	int32 GetCurDayElapsedMinutes();

	// 过去的总天数
	UFUNCTION(BlueprintCallable, Category = "DayLightSys")
	int32 GetElapsedDays();

	UFUNCTION(BlueprintCallable, Category = "DayLightSys")
	int32 GetElapsedDaysInMinutes();

	UFUNCTION(exec)
	void SetTime(int32 time);

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "DayLightSys")
	int32 m_iElapsedGameMinutes;

	UPROPERTY(EditDefaultsOnly, Category = "DayLightSys")
	float m_fTimeScale;

	UPROPERTY(Replicated)
	bool m_bIsNight;

	float m_fSunriseTimeMark;

	float m_fSunsetTimeMark;

	float m_fTotalMinutesPerDay;
};
