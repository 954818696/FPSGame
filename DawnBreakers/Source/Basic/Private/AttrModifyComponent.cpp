// Fill out your copyright notice in the Description page of Project Settings.

#include "AttrModifyComponent.h"
#include "Net/UnrealNetwork.h"
#include "AttrModifyInterface.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY(AttrModifyComponent);

UAttrModifyComponent::UAttrModifyComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;

	ConfigAttrModifyList.Empty();
	AttrRegisterItemMap.Empty();
	RelevantActors.Empty();

	SetActive(true);
	SetIsReplicated(true);
}

void UAttrModifyComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UAttrModifyComponent, AttrModifyStateList);
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

	if (RelevantActors.Num() == 0)
	{
		IAttrModifyInterface* AttrModifyInterface = Cast<IAttrModifyInterface>(Owner);
		if (AttrModifyInterface)
		{
			TArray<AActor*> Actors = AttrModifyInterface->Execute_GetRelevantActors(Owner);
			for (int32 i = 0; i < Actors.Num(); ++i)
			{
				RelevantActors.AddUnique(Actors[i]);
			}

			//RelevantActors.Append(Actors);
			if (RelevantActors.Num() == 0)
			{
				UE_LOG(AttrModifyComponent, Warning, TEXT("Actor:%s, AttrModifyComponent RelevantActors Num = 0!! please check!!!!"), *Owner->GetName());
			}
		}
	}

	AttrModifyStateList.Init(0, ConfigAttrModifyList.Num());

	return true;
}

bool UAttrModifyComponent::EnableAttrModifierByIndex(int32 ModifyConfigIndex)
{
	bool Result = false;
	AActor* Owner = GetOwner();
	if (Owner == nullptr ||
		ConfigAttrModifyList.IsValidIndex(ModifyConfigIndex) == false ||
		ConfigAttrModifyList[ModifyConfigIndex].IsEnable)
	{
		return Result;
	}

	for (int32 ActorIndex = 0; ActorIndex < RelevantActors.Num(); ++ActorIndex)
	{
		AActor* GetRelevantActor = RelevantActors[ActorIndex].Get();
		if (GetRelevantActor == nullptr || !GetRelevantActor->IsValidLowLevel())
		{
			continue;
		}

		IAttrModifyInterface* ActorAttrModifyInterface = Cast<IAttrModifyInterface>(GetRelevantActor);
		if (ActorAttrModifyInterface)
		{
			UAttrModifyComponent* ActorAttrModifyComp = ActorAttrModifyInterface->Execute_GetAttrModifyComponent(GetRelevantActor);
			if (ActorAttrModifyComp)
			{
				FAttrRegisterItem* ActorAttr = ActorAttrModifyComp->FindRegisterAttr(ConfigAttrModifyList[ModifyConfigIndex].AttrName);
				if (ActorAttr)
				{
					float CalcModifyAddValue = 0.f;
					switch (ConfigAttrModifyList[ModifyConfigIndex].ModifierOp)
					{
					case EAttrOperator::Set:
						CalcModifyAddValue = ConfigAttrModifyList[ModifyConfigIndex].ModifierValue - ActorAttr->OriginalValue;
						break;
					case EAttrOperator::Plus:
						CalcModifyAddValue = ConfigAttrModifyList[ModifyConfigIndex].ModifierValue;
						break;
					case EAttrOperator::Multiply:
						CalcModifyAddValue = (ConfigAttrModifyList[ModifyConfigIndex].ModifierValue - 1) * ActorAttr->OriginalValue;
						break;
					default:
						break;
					}

					if (Owner->Role == ROLE_Authority ||
						ActorAttr->HasReplicatedTag == false)
					{
						if (ActorAttr->AttrVariableType == EAttrVariableType::Int)
						{
							*((int32 *)ActorAttr->AttrDataPtr) += FMath::FloorToInt(CalcModifyAddValue);
						}
						else if (ActorAttr->AttrVariableType == EAttrVariableType::Float)
						{
							*((float *)ActorAttr->AttrDataPtr) += CalcModifyAddValue;
						}
						else
						{
							continue;
						}
					}

					FAttrModifyItem::SCacheAffactTargetInfo CacheAffactTargetInfo;
					CacheAffactTargetInfo.AffectTarget = GetRelevantActor;
					CacheAffactTargetInfo.FinalAddValue = CalcModifyAddValue;
					
					ConfigAttrModifyList[ModifyConfigIndex].AffectTargetsCachInfo.Add(CacheAffactTargetInfo);
				}
			}
		}
	}

	if (ConfigAttrModifyList[ModifyConfigIndex].AffectTargetsCachInfo.Num() > 0)
	{
		Result = true;
		ConfigAttrModifyList[ModifyConfigIndex].IsEnable = true;
		AttrModifyStateList[ModifyConfigIndex] = 1;
	}

	return Result;
}

bool UAttrModifyComponent::DisableAttrModifierByIndex(int32 ModifyConfigIndex)
{
	bool Result = false;

	if (ConfigAttrModifyList.IsValidIndex(ModifyConfigIndex) &&
		ConfigAttrModifyList[ModifyConfigIndex].IsEnable)
	{
		Result = true;
		for (int32 i = 0; i < ConfigAttrModifyList[ModifyConfigIndex].AffectTargetsCachInfo.Num(); ++i)
		{
			ConfigAttrModifyList[ModifyConfigIndex].RemoveModify(i);
		}

		ConfigAttrModifyList[ModifyConfigIndex].AffectTargetsCachInfo.Empty();
		ConfigAttrModifyList[ModifyConfigIndex].IsEnable = false;
		AttrModifyStateList[ModifyConfigIndex] = 0;
	}

	return Result;
}

void UAttrModifyComponent::OnRep_AttrModifyStateList()
{
	TArray<FAttrAffected> AffectedAttr;
	
	for (int32 i = 0; i < AttrModifyStateList.Num(); ++i)
	{
		if (AttrModifyStateList[i])
		{
			bool EnableSuccess = EnableAttrModifierByIndex(i);
			if (EnableSuccess)
			{
				for (int32 AffactTargetIndex = 0; AffactTargetIndex < ConfigAttrModifyList[i].AffectTargetsCachInfo.Num(); ++AffactTargetIndex)
				{
					AffectedAttr.AddUnique(FAttrAffected(ConfigAttrModifyList[i].AttrName,
						ConfigAttrModifyList[i].AffectTargetsCachInfo[AffactTargetIndex].AffectTarget.Get())
					);
				}
			}
		}
		else
		{
			bool DisableSuccess = DisableAttrModifierByIndex(i);
			if (DisableSuccess)
			{
				for (int32 AffactTargetIndex = 0; AffactTargetIndex < ConfigAttrModifyList[i].AffectTargetsCachInfo.Num(); ++AffactTargetIndex)
				{
					AffectedAttr.AddUnique(FAttrAffected(ConfigAttrModifyList[i].AttrName,
						ConfigAttrModifyList[i].AffectTargetsCachInfo[AffactTargetIndex].AffectTarget.Get())
					);
				}
			}
		}
	}

	OnAttrModified.Broadcast(AffectedAttr);
}

bool UAttrModifyComponent::EnableAttrModifier(FString AttrModifyItemName)
{
	bool Result = false;

	for (int32 i = 0; i < ConfigAttrModifyList.Num(); ++i)
	{
		if (AttrModifyItemName == ConfigAttrModifyList[i].AttrModifyItemName)
		{
			Result = EnableAttrModifierByIndex(i);
			break;
		}
	}

	// ToDo: for Event. replicate.
	
	return Result;
}

bool UAttrModifyComponent::DisableAttrModifier(FString AttrModifyItemName)
{
	bool Result = false;
	for (int32 i = 0; i < ConfigAttrModifyList.Num(); ++i)
	{
		if (AttrModifyItemName == ConfigAttrModifyList[i].AttrModifyItemName)
		{
			Result = DisableAttrModifierByIndex(i);
			break;
		}
	}

	return Result;
}

bool UAttrModifyComponent::EnableAllAttrModifier()
{
	bool Result = false;
	for (int32 i = 0; i < ConfigAttrModifyList.Num(); ++i)
	{
		Result = EnableAttrModifierByIndex(i);
	}

	return Result;
}

bool UAttrModifyComponent::DisableAllAttrModifier()
{
	bool Result = false;
	for (int32 i = 0; i < ConfigAttrModifyList.Num(); ++i)
	{
		Result = DisableAttrModifierByIndex(i);
	}

	return Result;
}

bool UAttrModifyComponent::DisableModifierToActor(AActor* TargetActor)
{
	for (int32 i = 0; i < ConfigAttrModifyList.Num(); ++i)
	{
		TArray<int32> AffectTargetCachIndice = ConfigAttrModifyList[i].GetAffectTargetCachIndex(TargetActor);

		for (int32 TargetIndex = 0; TargetIndex < AffectTargetCachIndice.Num(); ++TargetIndex)
		{
			ConfigAttrModifyList[i].RemoveModify(TargetIndex);
		}
		
		ConfigAttrModifyList[i].AffectTargetsCachInfo.RemoveAll([TargetActor](const FAttrModifyItem::SCacheAffactTargetInfo& Ptr)
		{
			return Ptr.AffectTarget.Get() == TargetActor;
		});
	}

	return true;
}

FAttrRegisterItem* UAttrModifyComponent::FindRegisterAttr(FString AttrName)
{
	FAttrRegisterItem* FindAttrRegisterItem = AttrRegisterItemMap.Find(AttrName);
	return FindAttrRegisterItem;
}


void FAttrModifyItem::RemoveModify(int32 index)
{
	AActor* AffactedTarget = AffectTargetsCachInfo[index].AffectTarget.Get();
	if (AffactedTarget == nullptr || !AffactedTarget->IsValidLowLevel())
	{
		return;
	}


	IAttrModifyInterface* ActorAttrModifyInterface = Cast<IAttrModifyInterface>(AffactedTarget);
	if (ActorAttrModifyInterface)
	{
		UAttrModifyComponent* ActorAttrModifyComp = ActorAttrModifyInterface->Execute_GetAttrModifyComponent(AffactedTarget);
		if (ActorAttrModifyComp)
		{
			FAttrRegisterItem* ActorAttr = ActorAttrModifyComp->FindRegisterAttr(AttrName);
			if (ActorAttr)
			{
				if (AffactedTarget->Role == ROLE_Authority ||
					ActorAttr->HasReplicatedTag == false)
				{
					float MinusValue = AffectTargetsCachInfo[index].FinalAddValue;
					if (ActorAttr->AttrVariableType == EAttrVariableType::Int)
					{
						*((int32 *)ActorAttr->AttrDataPtr) -= FMath::FloorToInt(MinusValue);
					}
					else if (ActorAttr->AttrVariableType == EAttrVariableType::Float)
					{
						*((float *)ActorAttr->AttrDataPtr) -= MinusValue;
					}
				}
			}
		}
	}
}

TArray<int32> FAttrModifyItem::GetAffectTargetCachIndex(AActor* Target)
{
	TArray<int32> OutResult;
	for (int32 i = 0; i < AffectTargetsCachInfo.Num(); ++i)
	{
		if (Target == AffectTargetsCachInfo[i].AffectTarget.Get())
		{
			OutResult.Add(i);
		}
	}

	return OutResult;
}
