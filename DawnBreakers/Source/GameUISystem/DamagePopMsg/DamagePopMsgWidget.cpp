// Fill out your copyright notice in the Description page of Project Settings.

#include "GameUISystem.h"
#include "DamagePopMsgWidget.h"

void UDamagePopMsgWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UDamagePopMsgWidget::Update(float Delta)
{
	if (IsRunningValid)
	{
		if (LifeTime > 0)
		{
			FVector2D ScreenPos;
			SetVisibility(ESlateVisibility::HitTestInvisible);
			PCOwner->ProjectWorldLocationToScreen(PopTextData.TargetLocation, ScreenPos);
			SetPositionInViewport(ScreenPos);
			LifeTime -= Delta;
		}
		else
		{
			//StopAnimation(CurPlayAnim);
			ResetAll();
			SetVisibility(ESlateVisibility::Hidden);
			IsRunningValid = false;
		}
	}
}

void UDamagePopMsgWidget::PlayPopAnim()
{
    if (PopTextData.PopDamageType == EPopDamageType::E_MissAtk)
	{
		int AnimIndex = FMath::RandRange(0, PopMissAnim.Num() - 1);
		CurPlayAnim = PopMissAnim[AnimIndex];
	}
	else
	{
		if (PopTextData.PopDamageType == EPopDamageType::E_CriticalAtk)
		{
			int AnimIndex = FMath::RandRange(0, PopCriticalAtkAnim.Num() - 1);
			CurPlayAnim = PopCriticalAtkAnim[AnimIndex];
		}
		else
		{
			int AnimIndex = FMath::RandRange(0, PopAnim.Num() - 1);
			CurPlayAnim = PopAnim[AnimIndex];
		}
	}

	PlayAnimation(CurPlayAnim);
}
