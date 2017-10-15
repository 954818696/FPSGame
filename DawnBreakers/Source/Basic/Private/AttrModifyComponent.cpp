// Fill out your copyright notice in the Description page of Project Settings.

#include "AttrModifyComponent.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(AttrModifyComponent);

UAttrModifyComponent::UAttrModifyComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	ConfigAttrModifyList.Empty();
	InEffectiveModifyList.Empty();
	AttrRegisterItemMap.Empty();

	SetActive(true);
	SetIsReplicated(true);
}

void UAttrModifyComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


}

bool UAttrModifyComponent::RegisterModifyAbleAttr(const TArray<FAttrRegisterItem>& AttrRegists)
{
	AActor* Owner = GetOwner();
	if (Owner == nullptr || !Owner->IsValidLowLevel())
	{
		UE_LOG(AttrModifyComponent, Error, TEXT("UAttrModifyComponent::RegisterModifyAbleAttr Invalid Owner!!!!"));
		return false;
	}

	for (int32 i = 0; i < AttrRegists.Num(); ++i)
	{
		if (AttrRegists[i].AttrName.IsEmpty())
		{
			UE_LOG(AttrModifyComponent, Warning, TEXT("Actor:%s, AttrModifyComponent has Null AttrName AttrRegisterItem, please check!!!!"), *Owner->GetName());
			continue;
		}

		if (AttrRegisterItemMap.Contains(AttrRegists[i].AttrName))
		{
			continue;
		}

		AttrRegisterItemMap.Add(AttrRegists[i].AttrName, AttrRegists[i]);

		if (AttrRegists[i].AttrDataPtr == nullptr)
		{
			FAttrRegisterItem* FindAttrRegisterItem = AttrRegisterItemMap.Find(AttrRegists[i].AttrName);
			if (FindAttrRegisterItem)
			{
				bool FoundDefineInBPAttr = false;
				if (AttrRegists[i].AttrVariableType == EAttrVariableType::Int)
				{
					UIntProperty* IntAttr = FindField<UIntProperty>(Owner->GetClass(), *AttrRegists[i].AttrName);
					if (IntAttr)
					{
						int32* FoundIntAttr = nullptr;
						FoundIntAttr = IntAttr->GetPropertyValuePtr_InContainer(Owner);
						if (FoundIntAttr)
						{
							FindAttrRegisterItem->AttrDataPtr = FoundIntAttr;
							FindAttrRegisterItem->OriginalValue = *FoundIntAttr;

							FoundDefineInBPAttr = true;	
						}
					}
				}
				else if (AttrRegists[i].AttrVariableType == EAttrVariableType::Float)
				{
					UFloatProperty* FloatAttr = FindField<UFloatProperty>(Owner->GetClass(), *AttrRegists[i].AttrName);
					if (FloatAttr)
					{
						float* FoundFloatAttr = nullptr;
						FoundFloatAttr = FloatAttr->GetPropertyValuePtr_InContainer(Owner);
						if (FoundFloatAttr)
						{
							FindAttrRegisterItem->AttrDataPtr = FoundFloatAttr;
							FindAttrRegisterItem->OriginalValue = *FoundFloatAttr;

							FoundDefineInBPAttr = true;
						}
					}
				}

				if (!FoundDefineInBPAttr)
				{
					UE_LOG(AttrModifyComponent, Warning, TEXT("Actor:%s, AttrModifyComponent not found AttrName %s define in BP, please check!!!!"), *Owner->GetName(), *AttrRegists[i].AttrName);
				}
			}
		}	
	}
	
	return true;
}

void UAttrModifyComponent::ReplicateNorRepAttr_Implementation(const TArray<float>& ValueList)
{

}

bool UAttrModifyComponent::EnableAttrModifier(FString AttrModifyItemName)
{
	return true;
}

bool UAttrModifyComponent::DisableAttrModifier(FString AttrModifyItemName)
{
	return true;
}

bool UAttrModifyComponent::EnableAllAttrModifier()
{
	return true;
}

bool UAttrModifyComponent::DisableAllAttrModifier()
{
	return true;
}

bool UAttrModifyComponent::DisableRelevantActorAttrModifier(AActor* RelevantActor)
{
	return true;
}


