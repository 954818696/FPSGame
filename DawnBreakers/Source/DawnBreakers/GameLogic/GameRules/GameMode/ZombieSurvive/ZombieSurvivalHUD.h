// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ZombieSurvivalHUD.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API AZombieSurvivalHUD : public AHUD
{
	GENERATED_UCLASS_BODY()
	
	
public:
	virtual void DrawHUD() override;

	FCanvasIcon DebugCenterDotIcon;
	void DrawDebugCrossHair();

	void DrawDefaultCrossHair();

	UFUNCTION(BlueprintImplementableEvent, Category = AZombieSurvivalHUD)
	void HandleMsg(const FString& Msg);

	UFUNCTION(BlueprintCallable, Category = AZombieSurvivalHUD)
	void SetHUDVisibility(bool bShow);

private:
	class UTexture2D* CrosshairTex;

	bool m_ShowHUD;
	
};
