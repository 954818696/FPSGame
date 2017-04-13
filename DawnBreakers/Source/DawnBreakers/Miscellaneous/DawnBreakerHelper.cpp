// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DawnBreakerHelper.h"

DawnBreakerHelper::DawnBreakerHelper()
{
}

DawnBreakerHelper::~DawnBreakerHelper()
{
}

UWorld* DawnBreakerHelper::GetGameWorld()
{
	UWorld* TWorld = GEngine->GetWorld();
	if (TWorld != nullptr)
	{
		UGameInstance* TGameInstance = TWorld->GetGameInstance();
		if (TGameInstance)
		{
			return TGameInstance->GetWorld();
		}
	}

	return nullptr;
}
