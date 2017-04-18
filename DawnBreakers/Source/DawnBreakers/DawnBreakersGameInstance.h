// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "DawnBreakersGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API UDawnBreakersGameInstance : public UGameInstance//, public FTickableGameObject
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

	virtual void Shutdown() override;
	
	void BeginLoadMap(const FString& MapName);

	//UFUNCTION()
	void EndLoadMap();


private:
	UPROPERTY()
	class ULevelLoadAssist* m_LevelLoadAssisit;
};
