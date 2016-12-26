// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DamagePopMsgWidget.h"
#include "DamagePopMsgSys.generated.h"

UCLASS()
class GAMEUISYSTEM_API ADamagePopMsgSys : public AActor
{
	GENERATED_BODY()
	
public:	
	ADamagePopMsgSys();

	virtual void BeginPlay() override;

	virtual void Tick( float DeltaSeconds ) override;

	virtual void PostInitializeComponents() override;
	
	void AddDamagePopMessage(const FPopTextData& newData);

private:
	UFUNCTION()
	void OnDamageEvent(int32 senderId, int32 target, int32 hp, bool isCrit);

	UFUNCTION()
	void OnDamageMiss(int32 senderId, int32 targetId);

	void SetWidgetsPCOwner();

public:

	UPROPERTY(EditAnywhere, Category = Config)
	TSubclassOf<class UDamagePopMsgWidget> PopMsgWidget;

	TArray<class UDamagePopMsgWidget *> PopMsgWidgetArray;

	TArray<FPopTextData> CachedPopTextDataArray;

	UPROPERTY(EditAnywhere, Category = Config)
	int32 MaxWidgetsNum;

	UPROPERTY(EditAnywhere, Category = Config)
	float WidgetLifeTime;

	UPROPERTY(EditAnywhere, Category = Config)
	FVector WidgetOffsetVector;

	class APlayerController* PCOwner;
};
