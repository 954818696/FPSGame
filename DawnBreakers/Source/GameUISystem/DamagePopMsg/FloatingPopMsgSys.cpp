// Fill out your copyright notice in the Description page of Project Settings.

#include "GameUISystem.h"
#include "FloatingPopMsgSys.h"


AFloatingPopMsgSys::AFloatingPopMsgSys()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AFloatingPopMsgSys::BeginPlay()
{
	Super::BeginPlay();

	//UEventSets::Instance()->OnFloatingPopMsgEvent.AddDynamic(this, &AFloatingPopMsgSys::OnFloatingPopMesseageEvent);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	for (int32 i = 0; i < PopMsgWidgetArray.Num(); ++i)
	{
		PopMsgWidgetArray[i]->SetCurrentPlayerController(PlayerController);
	}
}

void AFloatingPopMsgSys::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	for (int32 i = 0; i < PopMsgWidgetArray.Num(); ++i)
	{
		if (PopMsgWidgetArray[i]->IsEnabled())
		{
			PopMsgWidgetArray[i]->Update(DeltaTime);
		}
	}
}

void AFloatingPopMsgSys::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (PopMsgWidget && GetWorld())
	{
		for (int32 i = 0; i < MaxWidgetsNum; ++i)
		{
			UFloatingPopMsgWidget* tPopMsgWidget = NewObject<UFloatingPopMsgWidget>(GetWorld(), PopMsgWidget);
			if (tPopMsgWidget)
			{
				ULocalPlayer* tPlayer = GetWorld()->GetFirstLocalPlayerFromController(); 
				tPopMsgWidget->SetPlayerContext(FLocalPlayerContext(tPlayer));
				tPopMsgWidget->AddToViewport();
				tPopMsgWidget->SetVisibility(ESlateVisibility::Hidden);
				PopMsgWidgetArray.Add(tPopMsgWidget);
			}
		}
	}
}

void AFloatingPopMsgSys::AddDamagePopMessage(const FPopTextData & newData)
{
	int32 MostSuitableIndex = -1;
	float ComparedLifeTimeValue = MAX_FLT;

	for (int i = 0; i < PopMsgWidgetArray.Num(); ++i)
	{
		float LeftAnimPlayingTime = PopMsgWidgetArray[i]->GetAnimDuration();
		if (LeftAnimPlayingTime <= 0)
		{
			MostSuitableIndex = i;
			break;
		}
		else
		{
			if (LeftAnimPlayingTime < ComparedLifeTimeValue)
			{
				ComparedLifeTimeValue = LeftAnimPlayingTime;
				MostSuitableIndex = i;
			}
		}
	}

	if (MostSuitableIndex > -1)
	{
		PopMsgWidgetArray[MostSuitableIndex]->PopTextData = newData;
		PopMsgWidgetArray[MostSuitableIndex]->SetVisibility(ESlateVisibility::HitTestInvisible);
		PopMsgWidgetArray[MostSuitableIndex]->PlayPopAnim();
	}

	return;
}

void AFloatingPopMsgSys::OnFloatingPopMesseageEvent(const FVector& Position, const FString& Message, EFloatPopType FloatingType)
{
	FPopTextData NewTextData;

	NewTextData.PopText = FText::FromString(Message);
	NewTextData.FloatPopMsgType = FloatingType;
	NewTextData.TargetLocation += Position + WidgetOffset;

	AddDamagePopMessage(NewTextData);
}



