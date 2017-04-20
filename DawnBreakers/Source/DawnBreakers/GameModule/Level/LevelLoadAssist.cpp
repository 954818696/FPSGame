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
			m_SubLevelsPackageNameList = GetSubLevelsPackageName(TCurWorld);
			TCurWorld->GetTimerManager().SetTimer(TimerHandle_UpdateLoadProgress, this, &ULevelLoadAssist::UpdateLoadProgress, 0.1f, true);
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
	for (int32 i = 0; i < m_SubLevelsPackageNameList.Num(); ++i)
	{
		float TPercent = GetAsyncLoadPercentage(m_SubLevelsPackageNameList[i]);
		DAWNBREAKERS_LOG_INFO("%s Load Percent %f", *m_SubLevelsPackageNameList[i].ToString(), TPercent);
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("%s Load Percent %f"), *m_SubLevelsPackageNameList[i].ToString(), TPercent));
	}


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

TArray<FName> ULevelLoadAssist::GetSubLevelsPackageName(UWorld* InWorld)
{
	TArray<FName> Result;

	Result.Reserve(InWorld->StreamingLevels.Num());
	for (int32 LevelIndex = 0; LevelIndex < InWorld->StreamingLevels.Num(); LevelIndex++)
	{
		ULevelStreaming* LevelStreaming = InWorld->StreamingLevels[LevelIndex];
		if (LevelStreaming
			&& !LevelStreaming->GetWorldAsset().IsNull()
			&& LevelStreaming->GetWorldAsset() != InWorld)
		{
			Result.Add(LevelStreaming->GetWorldAssetPackageFName());
		}
	}
	
	return Result;
}

void ULevelLoadAssist::Clear()
{

}