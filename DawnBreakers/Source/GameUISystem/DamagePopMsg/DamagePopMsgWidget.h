// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "DamagePopMsgWidget.generated.h"

UENUM(BlueprintType)
enum class EPopDamageType :uint8
{
	E_NormalAtk = 1,
	E_CriticalAtk = 2,
	E_MissAtk = 3
};

USTRUCT(BlueprintType)
struct FPopTextData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FText PopText;

	UPROPERTY(BlueprintReadOnly)
	FVector TargetLocation; 

	EPopDamageType PopDamageType;
};

UCLASS()
class GAMEUISYSTEM_API UDamagePopMsgWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void PlayPopAnim();

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Pop Event")
	void OnShow(EPopDamageType type,const FString& content);

	UFUNCTION(BlueprintImplementableEvent, Category = "UDamagePopMsgWidget")
	void ResetAll();

public:

	UPROPERTY(BlueprintReadOnly)
	FPopTextData PopTextData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	TArray<class UWidgetAnimation*>  PopAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	TArray<class UWidgetAnimation*>  PopCriticalAtkAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UWidgetAnimation*  PlayerDamagedPopAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	TArray<class UWidgetAnimation*>   PopMissAnim;

	UWidgetAnimation* CurPlayAnim;

	float LifeTime;

	TWeakObjectPtr<APlayerController> PCOwner;

	void Update(float Delta);

	bool IsRunningValid;
};
