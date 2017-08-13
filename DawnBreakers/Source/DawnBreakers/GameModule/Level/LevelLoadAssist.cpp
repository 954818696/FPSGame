// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "LevelLoadAssist.h"

void ULevelLoadAssist::OnLoadMasterLevelBegin(const FString& MapName)
{
	m_LoadMapName = *MapName;
}

void ULevelLoadAssist::OnLoadMasterLevelFinish()
{
	FName SubLevel1(TEXT("Level_Loading"));
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName("LoadLoadingLevelFinish");
	LatentInfo.Linkage = 0;
	UWorld* TCurWorld = DawnBreakerHelper::GetGameWorld();
	if (TCurWorld)
	{
		m_SubLevelsPackageNameList = GetSubLevelsPackageName(TCurWorld);
		TCurWorld->GetTimerManager().SetTimer(TimerHandle_UpdateLoadProgress, this, &ULevelLoadAssist::UpdateLoadProgress, 0.01f, true, 0.f);
		UGameplayStatics::LoadStreamLevel(TCurWorld, SubLevel1, true, true, LatentInfo);

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



void ULevelLoadAssist::LoadLoadingLevelFinish()
{
	FName SubLevel(TEXT("Level1_Main"));
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName("AllSubLevelLoadFinish");
	LatentInfo.Linkage = 0;
	UWorld* TCurWorld = DawnBreakerHelper::GetGameWorld();
	if (TCurWorld && TCurWorld->IsValidLowLevel())
	{
		UpdateLoadProgress();
		UGameplayStatics::LoadStreamLevel(TCurWorld, SubLevel, true, false, LatentInfo);
	}

}

void ULevelLoadAssist::AllSubLevelLoadFinish()
{
	TimerHandle_UpdateLoadProgress.Invalidate();
	UpdateLoadProgress();
	UEventSets::Instance()->OnPreparedForGetInGame.Broadcast();
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

void ULevelLoadAssist::UpdateLoadProgress()
{
	for (int32 i = 0; i < m_SubLevelsPackageNameList.Num(); ++i)
	{
		float TPercent = GetAsyncLoadPercentage(m_SubLevelsPackageNameList[i]);
		TPercent = TPercent > 0 ? TPercent * 100.f : 100.f;
		UEventSets::Instance()->OnLevelStreamLoadPercent.Broadcast(TPercent);
	}

}


void ULevelLoadAssist::Clear()
{

}


