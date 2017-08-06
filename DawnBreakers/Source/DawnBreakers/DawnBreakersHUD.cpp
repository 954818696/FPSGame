// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "DawnBreakers.h"
#include "DawnBreakersHUD.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"

ADawnBreakersHUD::ADawnBreakersHUD()
{
	//static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshiarTexObjDebug(TEXT("/Game/UI/HUD/T_CenterDot_M.T_CenterDot_M"));
	//CrosshairTex = CrosshiarTexObjDebug.Object;

	//DebugCenterDotIcon = UCanvas::MakeIcon(CrosshiarTexObjDebug.Object);
}


void ADawnBreakersHUD::DrawHUD()
{
	Super::DrawHUD();

	//DrawDebugCrossHair();
}

void ADawnBreakersHUD::DrawDebugCrossHair()
{
	//float CenterX = Canvas->ClipX / 2;
	//float CenterY = Canvas->ClipY / 2;
	//float CenterDotScale = 0.07f;

	//Canvas->SetDrawColor(255, 255, 255, 255);
	//Canvas->DrawIcon(DebugCenterDotIcon,
	//	CenterX - DebugCenterDotIcon.UL * CenterDotScale / 2.0f,
	//	CenterY - DebugCenterDotIcon.VL * CenterDotScale / 2.0f, CenterDotScale);
}

void ADawnBreakersHUD::DrawDefaultCrossHair()
{
	// Draw very simple crosshair

	// find center of the Canvas
	//const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	//// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	//const FVector2D CrosshairDrawPosition(Center.X, Center.Y);

	//// draw the crosshair
	//FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	//TileItem.BlendMode = SE_BLEND_Translucent;
	//Canvas->DrawItem(TileItem);
}



