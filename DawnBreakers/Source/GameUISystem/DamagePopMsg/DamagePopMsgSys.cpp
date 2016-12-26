// Fill out your copyright notice in the Description page of Project Settings.

#include "GameUISystem.h"
#include "DamagePopMsgSys.h"
#include "DamagePopMsgWidget.h"


// Sets default values
ADamagePopMsgSys::ADamagePopMsgSys()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADamagePopMsgSys::BeginPlay()
{
	Super::BeginPlay();

	//UEventManager::Get()->OnDamageHp.AddDynamic(this, &ADamagePopMsgSys::OnDamageEvent);
	//UEventManager::Get()->OnDamageMiss.AddDynamic(this, &ADamagePopMsgSys::OnDamageMiss);

	SetWidgetsPCOwner();
}

// Called every frame
void ADamagePopMsgSys::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	for (int i = 0; i < PopMsgWidgetArray.Num(); ++i)
	{
		PopMsgWidgetArray[i]->Update(DeltaTime);
	}
}

void ADamagePopMsgSys::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PCOwner = GetWorld()->GetFirstPlayerController();
	for (int i = 0; i < MaxWidgetsNum; ++i)
	{
		FPopTextData tData;
		tData.PopText = FText::FromString("");
		tData.TargetLocation = FVector::ZeroVector;
		CachedPopTextDataArray.Add(tData);
	}

	if (PopMsgWidget && GetWorld())
	{
		for (int i = 0; i < MaxWidgetsNum; ++i)
		{
			// 加载日后需要统一接口加载，此处留备注
			UDamagePopMsgWidget* tPopMsgWidget = NewObject<UDamagePopMsgWidget>(GetWorld(), PopMsgWidget);
			if (tPopMsgWidget)
			{
				ULocalPlayer* tPlayer = GetWorld()->GetFirstLocalPlayerFromController(); 
				tPopMsgWidget->SetPlayerContext(FLocalPlayerContext(tPlayer));
				
				tPopMsgWidget->LifeTime = 0;
				tPopMsgWidget->AddToViewport();
				tPopMsgWidget->SetVisibility(ESlateVisibility::Hidden);
				tPopMsgWidget->IsRunningValid = false;
				PopMsgWidgetArray.Add(tPopMsgWidget);
			}
		}
	}
}

void ADamagePopMsgSys::AddDamagePopMessage(const FPopTextData & newData)
{
	int32 ResultIndex = 0;
	float tLifeTime = PopMsgWidgetArray[0]->LifeTime;

	for (int i = 0; i < MaxWidgetsNum; ++i)
	{
		if (PopMsgWidgetArray[i]->LifeTime <= 0)
		{
			ResultIndex = i;
			break;
		}
		else
		{
			if (PopMsgWidgetArray[i]->LifeTime < tLifeTime)
			{
				tLifeTime = PopMsgWidgetArray[i]->LifeTime;
				ResultIndex = i;
			}
		}
	}
	PopMsgWidgetArray[ResultIndex]->PopTextData = newData;
	PopMsgWidgetArray[ResultIndex]->PopTextData.TargetLocation += WidgetOffsetVector;
	PopMsgWidgetArray[ResultIndex]->LifeTime = WidgetLifeTime;
	PopMsgWidgetArray[ResultIndex]-> IsRunningValid = true;
	PopMsgWidgetArray[ResultIndex]->PlayPopAnim();
	PopMsgWidgetArray[ResultIndex]->SetVisibility(ESlateVisibility::HitTestInvisible);

	FString str = newData.PopText.ToString();
	PopMsgWidgetArray[ResultIndex]->OnShow(newData.PopDamageType,str);

	return;
}

void ADamagePopMsgSys::OnDamageEvent(int32 senderId, int32 target, int32 hp, bool isCrit)
{
	struct FPopTextData NewTextData;

	if (isCrit)
	{
		NewTextData.PopDamageType = EPopDamageType::E_CriticalAtk;
	}
	else
	{
		NewTextData.PopDamageType = EPopDamageType::E_NormalAtk;
	}

	NewTextData.PopText = FText::FromString(FString::Printf(TEXT("%d"), (int32)hp));
	
	//NewTextData.TargetLocation = TargetPawn->GetActorLocation();

	AddDamagePopMessage(NewTextData);
}

void ADamagePopMsgSys::OnDamageMiss(int32 senderId, int32 targetId)
{
	struct FPopTextData NewTextData;
	NewTextData.PopDamageType = EPopDamageType::E_MissAtk;
	NewTextData.PopText = FText::FromString(TEXT(""));
	//NewTextData.TargetLocation = TargetPawn->GetActorLocation();

	AddDamagePopMessage(NewTextData);
}

void ADamagePopMsgSys::SetWidgetsPCOwner()
{
	PCOwner = GetWorld()->GetFirstPlayerController();
	for (int i = 0; i < PopMsgWidgetArray.Num(); ++i)
	{
		PopMsgWidgetArray[i]->PCOwner = PCOwner;
	}
}

