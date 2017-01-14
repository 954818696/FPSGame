// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "FloatingPopMsgWidget.generated.h"

UENUM(BlueprintType)
enum class EFloatPopType :uint8
{
	E_PopType1 = 0,
	E_PopType2 = 1,
	E_PopType3 = 2,
};

USTRUCT(BlueprintType)
struct FPopTextData
{
	GENERATED_USTRUCT_BODY()

public:

	FPopTextData()
	{
		PopText = FText::FromString("");
		TargetLocation = FVector::ZeroVector;
		FloatPopMsgType = EFloatPopType::E_PopType1;
	}

	//FPopTextData(const FPopTextData& Data)
	//{
	//	PopText = Data.PopText;
	//	TargetLocation = Data.TargetLocation;
	//	FloatPopMsgType = Data.FloatPopMsgType;
	//}

	UPROPERTY(BlueprintReadOnly)
	FText PopText;

	UPROPERTY(BlueprintReadOnly)
	FVector TargetLocation; 

	EFloatPopType FloatPopMsgType;
};

UCLASS(ABSTRACT)
class  UFloatingPopMsgWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void PlayPopAnim();

	void Update(float Delta);

	FORCEINLINE void SetCurrentPlayerController(APlayerController* PlayerController)
	{
		CurrentPlayerController = PlayerController;
	}

	FORCEINLINE float GetAnimDuration() const
	{
		return AnimDuration;
	}

	FORCEINLINE bool IsEnabled() const
	{
		return IsPlayingAnimtion;
	}

public:
	UPROPERTY(BlueprintReadOnly)
	FPopTextData PopTextData;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	TArray<class UWidgetAnimation*>  PopAnim;

private:
	bool IsPlayingAnimtion;

	float AnimDuration;

	TWeakObjectPtr<APlayerController> CurrentPlayerController;
};

