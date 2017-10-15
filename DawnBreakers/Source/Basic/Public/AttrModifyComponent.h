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

	struct SCacheAffactTargetInfo
	{
		AActor* AffectTarget;
		float	FinalAddValue;

		SCacheAffactTargetInfo()
		{
			AffectTarget = nullptr;
			FinalAddValue = 0.f;
		}
	};

	TArray<SCacheAffactTargetInfo> AffectTargets;

	FAttrModifyItem()
	{
		AffectTargets.Empty();
	}

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASIC_API UAttrModifyComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttrModifiedEvent, FString, AttrName);
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
	bool DisableRelevantActorAttrModifier(AActor* RelevantActor);

private:
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
	TArray<FAttrModifyItem*> InEffectiveModifyList;
	TMap<FString, FAttrRegisterItem> AttrRegisterItemMap;
	
};
