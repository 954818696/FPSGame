// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "ZombieSurvivalHUD.h"


AZombieSurvivalHUD::AZombieSurvivalHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	m_ShowHUD(true)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshiarTexObjDebug(TEXT("/Game/UI/HUD/T_CenterDot_M.T_CenterDot_M"));
	CrosshairTex = CrosshiarTexObjDebug.Object;

	DebugCenterDotIcon = UCanvas::MakeIcon(CrosshiarTexObjDebug.Object);
}

void AZombieSurvivalHUD::DrawHUD()
{
	Super::DrawHUD();

	ADBCharacter* ControlledPawn = Cast<ADBCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (m_ShowHUD == false)
	{
		return;
	}
	if (ControlledPawn && ControlledPawn->GetHoldWeapon() == nullptr)
	{
		DrawDebugCrossHair();
	}
}

void AZombieSurvivalHUD::DrawDebugCrossHair()
{
	float CenterX = Canvas->ClipX / 2;
	float CenterY = Canvas->ClipY / 2;
	float CenterDotScale = 0.07f;

	Canvas->SetDrawColor(255, 255, 255, 255);
	Canvas->DrawIcon(DebugCenterDotIcon,
					 CenterX - DebugCenterDotIcon.UL * CenterDotScale / 2.0f,
					 CenterY - DebugCenterDotIcon.VL * CenterDotScale / 2.0f, 
					 CenterDotScale);
}

void AZombieSurvivalHUD::DrawDefaultCrossHair()
{
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	const FVector2D CrosshairDrawPosition(Center.X, Center.Y);

	FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}

void AZombieSurvivalHUD::SetHUDVisibility(bool bShow)
{
	m_ShowHUD = bShow;
}
