// Fill out your copyright notice in the Description page of Project Settings.

#include "TestAttrModifyActor.h"


// Sets default values
ATestAttrModifyActor::ATestAttrModifyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttrModifyComp = CreateDefaultSubobject<UAttrModifyComponent>(TEXT("AttrModifyComponent"));

	IntegerAttr = 1024;
	FloatAttr = 128.128;
	
	// Register.

	TArray<FAttrRegisterItem> RegAttr;
	FAttrRegisterItem IntegerReg, FloatReg;
	IntegerReg.AttrName = TEXT("IntegerAttr");
	IntegerReg.AttrVariableType = EAttrVariableType::Int;
	IntegerReg.AttrDataPtr = &IntegerAttr;
	IntegerReg.OriginalValue = IntegerAttr;
	RegAttr.Add(IntegerReg);

	FloatReg.AttrName = TEXT("FloatAttr");
	FloatReg.AttrVariableType = EAttrVariableType::Float;
	FloatReg.AttrDataPtr = &FloatAttr;
	FloatReg.OriginalValue = FloatAttr;
	RegAttr.Add(FloatReg);

	AttrModifyComp->RegisterModifyAbleAttr(RegAttr);

}

UAttrModifyComponent* ATestAttrModifyActor::GetAttrModifyComponent_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("ATestAttrModifyActor GetAttrModifyComponent_Implementation"));

	return AttrModifyComp;
}

TArray<AActor*> ATestAttrModifyActor::GetRelevantActors_Implementation()
{
	TArray<AActor*> OutTargets;
	OutTargets.Add(this);

	UE_LOG(LogTemp, Error, TEXT("ATestAttrModifyActor GetRelevantActors_Implementation"));

	return OutTargets;
}

// Called when the game starts or when spawned
void ATestAttrModifyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ATestAttrModifyActor::TestGetVariable()
{
	UIntProperty* IntProp = FindField<UIntProperty>(GetClass(), TEXT("xubowen"));
	if (IntProp)
	{
		int32* FoundInt = nullptr;
		FoundInt = IntProp->GetPropertyValuePtr_InContainer(this);
		if (FoundInt)
		{
			*FoundInt = 100;
			return true;
		}
	}
	return false;
}

// Called every frame
void ATestAttrModifyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

