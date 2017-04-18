// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "LevelLoadAssist.h"

void ULevelLoadAssist::OnLoadMasterLevelBegin(const FString& MapName)
{
	m_LoadMapName = *MapName;
}

void ULevelLoadAssist::OnLoadMasterLevelFinish()
{
	// Switch. extend in the future.
	{
		FName SubLevel(TEXT("Level_Loading"));
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		LatentInfo.ExecutionFunction = FName("LoadSubLevelFinish");
		LatentInfo.Linkage = 0;
		UWorld* TCurWorld = DawnBreakerHelper::GetGameWorld();
		if (TCurWorld && TCurWorld->IsValidLowLevel())
		{
			TCurWorld->GetTimerManager().SetTimer(TimerHandle_UpdateLoadProgress, this, &ULevelLoadAssist::UpdateLoadProgress, 1.f, true);
			UGameplayStatics::LoadStreamLevel(TCurWorld, SubLevel, true, false, LatentInfo);
		}
	}


}

void ULevelLoadAssist::OpenStoryModeLevel(const FName& PersistLevelName)
{
	UWorld* TGameWorld = DawnBreakerHelper::GetGameWorld();

	UGameplayStatics::OpenLevel(TGameWorld, PersistLevelName);
}

void ULevelLoadAssist::OpenMultiplayerLevel(const FName& LevelName)
{

}

void ULevelLoadAssist::UpdateLoadProgress()
{
	float TPercent = GetAsyncLoadPercentage(TEXT("Level1_Main"));
	DAWNBREAKERS_LOG_INFO("Load Percent %f", TPercent);
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Load Percent %f"), TPercent));
}

void ULevelLoadAssist::LoadSubLevelFinish()
{
	//UWorld* TCurWorld = DawnBreakerHelper::GetGameWorld();
	//if (TCurWorld && TCurWorld->IsValidLowLevel())
	//{
	//	TCurWorld->GetTimerManager().ClearTimer(TimerHandle_UpdateLoadProgress);
	//}


	{
		FName SubLevel(TEXT("Level1_Main"));
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		LatentInfo.ExecutionFunction = FName("Clear");
		LatentInfo.Linkage = 0;
		UWorld* TCurWorld = DawnBreakerHelper::GetGameWorld();
		if (TCurWorld && TCurWorld->IsValidLowLevel())
		{
			//TCurWorld->GetTimerManager().SetTimer(TimerHandle_UpdateLoadProgress, this, &ULevelLoadAssist::UpdateLoadProgress, 1.f, true);
			UGameplayStatics::LoadStreamLevel(TCurWorld, SubLevel, true, false, LatentInfo);
		}
	}
}

void ULevelLoadAssist::Clear()
{

}