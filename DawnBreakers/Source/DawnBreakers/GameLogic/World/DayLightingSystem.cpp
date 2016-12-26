// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DayLightingSystem.h"
#include "GameLogic/GameRules/DGameState.h"

// Sets default values
ADayLightingSystem::ADayLightingSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	SetReplicates(true);

	mfRequiredCaptureDelta = 0.01f;
}

// Called when the game starts or when spawned
void ADayLightingSystem::BeginPlay()
{
	Super::BeginPlay();
	
	if (mPrimarySunLight)
	{
		mfOriginalSunBrightness = mPrimarySunLight->GetBrightness();
		mfTargetSunBrightness = mfOriginalSunBrightness;
	}
}

// Called every frame
void ADayLightingSystem::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	
	ADGameState* MyGameState = Cast<ADGameState>(GetWorld()->GetGameState());
	if (MyGameState)
	{
		// 太阳光设置 日照方向
		if (mPrimarySunLight)
		{
			if (miLastServerUpdateTime == MyGameState->miElapsedGameMinutes)
			{
				miTimeIncrement += DeltaTime;
			}
			else
			{
				miTimeIncrement = 0;
			}

			const float fSimIncrement = MyGameState->GetTimeOfDayIncrement() * miTimeIncrement;
			const float PitchOffset = 90;
			const float PitchRotation = 360 * ((MyGameState->miElapsedGameMinutes + fSimIncrement) / MyGameState->mfTotalMinutesPerDay);

			FRotator NewSunRotation = FRotator(PitchRotation + PitchOffset, 45.f, 0);
			mPrimarySunLight->SetActorRelativeRotation(NewSunRotation);

			miLastServerUpdateTime = MyGameState->miElapsedGameMinutes;
		}

		// 光照强度
		if (MyGameState->mbIsNight != mbLastIsNight)
		{
			if (MyGameState->mbIsNight)
			{
				mfTargetSunBrightness = 0.01f;
			}
			else
			{
				mfTargetSunBrightness = mfOriginalSunBrightness;
			}
		}

		const float fLerpSpeed = 0.1 * GetWorldSettings()->GetEffectiveTimeDilation();
		float fCurSunBrightness = mPrimarySunLight->GetBrightness();
		float fNewBrightness = FMath::Lerp(fCurSunBrightness, mfTargetSunBrightness, fLerpSpeed);
		mPrimarySunLight->SetBrightness(fNewBrightness);

		mbLastIsNight = MyGameState->mbIsNight;

		// 环境光设置
		// 照度 时间0-12-24点对应0-1-0 alpha
		if (mSkyLight)
		{
			const float fAlpha = FMath::Sin(MyGameState->GetCurDayElapsedMinutes() / MyGameState->mfTotalMinutesPerDay * 3.14);
			const float fNewIntensity = FMath::Lerp(0.1, 1.0, fAlpha);
			mSkyLight->GetLightComponent()->SetIntensity(fNewIntensity);

			if (mfRequiredCaptureDelta < FMath::Abs(fNewIntensity - mfLastCapturedIntensity))
			{
				mSkyLight->GetLightComponent()->RecaptureSky();
				mfLastCapturedIntensity = fNewIntensity;
			}
		}
	}
}

