// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DayLightingSystem.generated.h"

UCLASS()
class DAWNBREAKERS_API ADayLightingSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADayLightingSystem();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	int32 miLastServerUpdateTime;
	int32 miTimeIncrement;

	UPROPERTY(BlueprintReadWrite, Category = "DayNight")
	ADirectionalLight* mPrimarySunLight;

	UPROPERTY(BlueprintReadWrite, Category = "DayNight")
	ASkyLight* mSkyLight;

protected:
	float mfOriginalSunBrightness;
	
	float mfTargetSunBrightness;

	float mfRequiredCaptureDelta;
	float mfLastCapturedIntensity;
	
	bool mbLastIsNight;


};
