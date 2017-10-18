// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "AttrModifyInterface.h"
#include "TestAttrModifyActor.generated.h"

UCLASS()
class ATestAttrModifyActor : public AActor, public IAttrModifyInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestAttrModifyActor();

	virtual UAttrModifyComponent* GetAttrModifyComponent_Implementation() override;

	virtual TArray<AActor*> GetRelevantActors_Implementation() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = test)
	bool TestGetVariable();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = test)
	float GetFloatAttr() { return FloatAttr; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attr)
	UAttrModifyComponent* AttrModifyComp;

private:


	int32 IntegerAttr;

	float FloatAttr;

	
	
};
