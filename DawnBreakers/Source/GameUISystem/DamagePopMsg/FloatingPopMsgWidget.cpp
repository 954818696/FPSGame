// Fill out your copyright notice in the Description page of Project Settings.

#include "GameUISystem.h"
#include "FloatingPopMsgWidget.h"
#include "Runtime/UMG/Public/Animation/WidgetAnimation.h"


void UFloatingPopMsgWidget::Update(float Delta)
{
	if (IsPlayingAnimtion)
	{
		if (AnimDuration > 0)
		{
			FVector2D ScreenPos;
			SetVisibility(ESlateVisibility::HitTestInvisible);
			CurrentPlayerController->ProjectWorldLocationToScreen(PopTextData.TargetLocation, ScreenPos);
			SetPositionInViewport(ScreenPos);
			AnimDuration -= Delta;
		}
		else
		{
			SetVisibility(ESlateVisibility::Hidden);
			IsPlayingAnimtion = false;
		}
	}
}

void UFloatingPopMsgWidget::PlayPopAnim()
{
	UWidgetAnimation* AnimToPlay;
	int32 AnimIndex = (int32)PopTextData.FloatPopMsgType;
	if (PopAnim.IsValidIndex(AnimIndex))
	{
		AnimToPlay = PopAnim[AnimIndex];
		AnimDuration = AnimToPlay->GetEndTime() - AnimToPlay->GetStartTime();
		IsPlayingAnimtion = true;
		PlayAnimation(AnimToPlay);
	}
}
