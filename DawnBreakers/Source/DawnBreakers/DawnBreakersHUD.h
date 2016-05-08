// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "DawnBreakersHUD.generated.h"

UCLASS()
class ADawnBreakersHUD : public AHUD
{
	GENERATED_BODY()

public:
	ADawnBreakersHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	FCanvasIcon DebugCenterDotIcon;
	void DrawDebugCrossHair();

	void DrawDefaultCrossHair();

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

