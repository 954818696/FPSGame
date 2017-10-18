// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttrModifyComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(AttrModifyComponent, All, All)

UENUM()
enum class EAttrOperator : uint8
{
	Plus		UMETA(DisplayName = "+"),
	Multiply	UMETA(DisplayName = "x"),
	Set			UMETA(DisplayName = "="),
};

UENUM()
enum class EAttrVariableType : uint8
{
	Int,
	Float,
};

USTRUCT(BlueprintType)
struct FAttrRegisterItem
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = AttrRegisterItem)
	FString AttrName;

	UPROPERTY(BlueprintReadWrite, Category = AttrRegisterItem)
	EAttrVariableType AttrVariableType = EAttrVariableType::Int;

	void* AttrDataPtr;

	float OriginalValue;

	FAttrRegisterItem()
	{
		AttrName = TEXT("");
		AttrDataPtr = nullptr;
		OriginalValue = 0.f;
	}
};

USTRUCT()
struct FAttrModifyItem
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = AttrModifyItem)
	FString AttrModifyItemName;

	UPROPERTY(EditAnywhere, Category = AttrModifyItem)
	FString AttrName;

	UPROPERTY(EditAnywhere, Category = AttrModifyItem)
	EAttrOperator ModifierOp = EAttrOperator::Set;

	UPROPERTY(EditAnywhere, Category = AttrModifyItem)
	bool AffactToAllRelevant = false;

	UPROPERTY(EditAnywhere, Category = AttrModifyItem)
	float ModifierValue;

	bool IsEnable;

	struct SCacheAffactTargetInfo
	{
		TWeakObjectPtr<AActor> AffectTarget;
		float	FinalAddValue;

		SCacheAffactTargetInfo()
		{
			ResetData();
		}

		void ResetData()
		{
			AffectTarget.Reset();
			FinalAddValue = 0.f;
		}
	};

	TArray<SCacheAffactTargetInfo> AffectTargetsCachInfo;

	FAttrModifyItem()
	{
		AffectTargetsCachInfo.Empty();
		IsEnable = false;
	}


	void RemoveModify(int32 index);

	TArray<int32> GetAffectTargetCachIndex(AActor* Target);


};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASIC_API UAttrModifyComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttrModifiedEvent, TArray<FAttrRegisterItem>, AttrName);
public:	
	UFUNCTION(BlueprintCallable, Category = AttrModifyComponent)
	bool RegisterModifyAbleAttr(const TArray<FAttrRegisterItem>& AttrRegists);

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = AttrModifyComponent)
	bool EnableAttrModifier(FString AttrModifyItemName);

	UFUNCTION(BlueprintCallable, Category = AttrModifyComponent)
	bool DisableAttrModifier(FString AttrModifyItemName);

	UFUNCTION(BlueprintCallable, Category = AttrModifyComponent)
	bool EnableAllAttrModifier();

	UFUNCTION(BlueprintCallable, Category = AttrModifyComponent)
	bool DisableAllAttrModifier();

	UFUNCTION(BlueprintCallable, Category = AttrModifyComponent)
	bool DisableModifierToActor(AActor* TargetActor);

	FAttrRegisterItem* FindRegisterAttr(FString AttrName);

private:
	bool EnableAttrModifierByIndex(int32 ModifyConfigIndex);

	bool DisableAttrModifierByIndex(int32 ModifyConfigIndex);

	UFUNCTION(Client, Reliable)
	void ReplicateNorRepAttr(const TArray<float>& ValueList);


// Variable...
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "TFOL_EventSet")
	FOnAttrModifiedEvent OnAttrModified;

protected:
	UPROPERTY(EditDefaultsOnly, Category = AttrModifyConfig)
	TArray<FAttrModifyItem> ConfigAttrModifyList;

private:
	TMap<FString, FAttrRegisterItem> AttrRegisterItemMap;

	TArray<TWeakObjectPtr<AActor>> RelevantActors;
	
};
