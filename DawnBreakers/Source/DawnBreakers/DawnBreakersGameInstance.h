// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "DawnBreakersGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API UDawnBreakersGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

	virtual void Shutdown() override;
	
	void BeginLoadMap(const FString& MapName);

	//UFUNCTION()
	void EndLoadMap();


private:
	TSharedPtr<class LevelAssist> m_LevelAssist;
};
