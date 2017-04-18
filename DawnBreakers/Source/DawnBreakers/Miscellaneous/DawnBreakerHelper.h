// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class DAWNBREAKERS_API DawnBreakerHelper
{
public:
	DawnBreakerHelper();
	~DawnBreakerHelper();

	static UWorld* GetGameWorld();

	static void SaveGameInstance(UGameInstance* NewGameInstance);

private:
	static UGameInstance* m_GameIntance;
};
