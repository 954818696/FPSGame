// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FloatingPopMsgWidget.h"
#include "FloatingPopMsgSys.generated.h"

UCLASS()
class  AFloatingPopMsgSys : public AActor
{
	GENERATED_BODY()
	
public:	
	AFloatingPopMsgSys();

	virtual void BeginPlay() override;

	virtual void Tick( float DeltaSeconds ) override;

	virtual void PostInitializeComponents() override;
	
	void AddDamagePopMessage(const FPopTextData& newData);

private:
	UFUNCTION()
	void OnFloatingPopMesseageEvent(const FVector& Position, const FString& Message, EFloatPopType FloatingType);

public:
	/* Floating pop message widget.*/
	UPROPERTY(EditAnywhere, Category = Config)
	TSubclassOf<class UFloatingPopMsgWidget> PopMsgWidget;

	/* The amount of floating pop message, using pool to cache the pop message widgets,  avoid spawn every time. */
	UPROPERTY(EditAnywhere, Category = Config)
	int32 MaxWidgetsNum;

	/* Adjust floating pop message spawn position. */
	UPROPERTY(EditAnywhere, Category = Config)
	FVector WidgetOffset;

private:
	float WidgetLifeTime;

	class APlayerController* CurrentPlayerController;

	TArray<class UFloatingPopMsgWidget *> PopMsgWidgetArray;
};
