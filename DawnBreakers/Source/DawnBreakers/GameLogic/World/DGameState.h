// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "DGameState.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API ADGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	ADGameState();

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
	void SetTime(float time);

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "DayLightSys")
	int32 miElapsedGameMinutes;

	UPROPERTY(EditDefaultsOnly, Category = "DayLightSys")
	float mfTimeScale;

	UPROPERTY(Replicated)
	bool mbIsNight;

	float mfSunriseTimeMark;

	float mfSunsetTimeMark;

	float mfTotalMinutesPerDay;
};
