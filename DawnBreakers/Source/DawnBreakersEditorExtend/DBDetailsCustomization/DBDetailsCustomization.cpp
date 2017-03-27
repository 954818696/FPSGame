#include "DawnBreakersEditorExtend.h"

#include "DawnBreakers/GameLogic/Item/Equip/Weapon/DBWeaponBase.h"
#include "DawnBreakers/GameLogic/Item/Equip/Weapon/WeaponState/DBWeaponStateFiring.h"

#include "Particles/ParticleSystemComponent.h"
#include "Runtime/Slate/Public/SlateBasics.h"
#include "DBDetailsCustomization.h"

#if WITH_EDITOR
#include "IDetailCustomNodeBuilder.h"
#include "DetailCategoryBuilder.h"
#include "IDetailPropertyRow.h"
#include "IDetailChildrenBuilder.h"
#include "DetailWidgetRow.h"
#include "PropertyHandle.h"
#include "IDetailsView.h"
#include "IPropertyUtilities.h"
#include "PropertyCustomizationHelpers.h"
//#include "Runtime/Slate/Public/Widgets/Input/SComboBox.h"

struct FFireShotParticleCompChoice
{
	FFireShotParticleCompChoice()
		:PSC(nullptr), DisplayName(NAME_None)
	{}

	FFireShotParticleCompChoice(const TWeakObjectPtr<UParticleSystemComponent>& InPSC, const FName& InName)
		:PSC(InPSC), DisplayName(InName)
	{}

	bool operator == (const FFireShotParticleCompChoice& Other)
	{
		return PSC == Other.PSC;
	}
	
	bool operator != (const FFireShotParticleCompChoice& Other)
	{
		return PSC != Other.PSC;
	}

	TWeakObjectPtr<UParticleSystemComponent> PSC;
	FName DisplayName;
};

struct FFireShotEffectItem : public TSharedFromThis<FFireShotEffectItem>
{
	FFireShotEffectItem(uint32 InIndex, TWeakObjectPtr<UObject> InObj, const TArray<TSharedPtr<FFireShotParticleCompChoice>>& InChoices)
		: Index(InIndex), Obj(InObj), Choices(InChoices)
	{
	}

	TSharedRef<SWidget> GenerateWidget(TSharedPtr<FFireShotParticleCompChoice> InItem)
	{
		return SNew(SBox)
			.Padding(5)
			[
				SNew(STextBlock)
				.Text(FText::FromName(InItem->DisplayName))
			];
	}

	void ComboChanged(TSharedPtr<FFireShotParticleCompChoice> NewSelection, ESelectInfo::Type SelectInfo)
	{
		if (Obj.IsValid())
		{
			UParticleSystemComponent* NewValue = NewSelection->PSC.Get();
			UDBWeaponStateFiring* FireState = Cast<UDBWeaponStateFiring>(Obj.Get());
			if (FireState != NULL)
			{
				if (FireState->m_FiringEffects.IsValidIndex(Index))
				{
					FireState->m_FiringEffects[Index] = NewValue;
					TextBlock->SetText(NewSelection->DisplayName.ToString());
				}
			}
		}
	}

	TSharedRef<SComboBox<TSharedPtr<FFireShotParticleCompChoice>>> CreateWidget()
	{
		FString CurrentText;
		{
			UParticleSystemComponent* CurrentValue = NULL;
			UDBWeaponStateFiring* FireState = Cast<UDBWeaponStateFiring>(Obj.Get());
			if (FireState != NULL)
			{
				CurrentValue = FireState->m_FiringEffects[Index];
			}

			for (int32 i = 0; i < Choices.Num(); i++)
			{
				if (Choices[i]->PSC == CurrentValue)
				{
					CurrentText = Choices[i]->DisplayName.ToString();
				}
			}
		}

		return SNew(SComboBox<TSharedPtr<FFireShotParticleCompChoice>>)
			.OptionsSource(&Choices)
			.OnGenerateWidget(this, &FFireShotEffectItem::GenerateWidget)
			.OnSelectionChanged(this, &FFireShotEffectItem::ComboChanged)
			.Content()
			[
				SAssignNew(TextBlock, STextBlock)
				.Text(FText::FromString(CurrentText))
			];
	}

	int32 Index;
	TWeakObjectPtr<UObject> Obj;
	const TArray<TSharedPtr<FFireShotParticleCompChoice>>& Choices;
	TSharedPtr<STextBlock> TextBlock;
};

class FFireShotEffectArrayBuilder : public FDetailArrayBuilder
{
public:
	FFireShotEffectArrayBuilder(TWeakObjectPtr<UObject> InObj, TSharedRef<IPropertyHandle> InBaseProperty, TArray<TSharedPtr<FFireShotParticleCompChoice>>& InChoices, bool InGenerateHeader = true)
		: FDetailArrayBuilder(InBaseProperty, InGenerateHeader), Obj(InObj), Choices(InChoices), MyArrayProperty(InBaseProperty->AsArray())
	{}

	virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override
	{
		uint32 NumChildren = 0;
		MyArrayProperty->GetNumElements(NumChildren);

		FireShotEffectEntries.SetNum(NumChildren);
		for (uint32 ChildIndex = 0; ChildIndex < NumChildren; ++ChildIndex)
		{
			TSharedPtr<FFireShotEffectItem> NewEntry = MakeShareable(new FFireShotEffectItem(ChildIndex, Obj, Choices));
			FireShotEffectEntries[ChildIndex] = NewEntry;

			TSharedRef<IPropertyHandle> ElementHandle = MyArrayProperty->GetElement(ChildIndex);
			ChildrenBuilder.AddChildContent(FText::FromString(TEXT("MuzzleFlash")))
				.NameContent()
				[
					ElementHandle->CreatePropertyNameWidget()
				]
			.ValueContent()
				[
					NewEntry->CreateWidget()
				];
		}
	}

	TWeakObjectPtr<UObject> Obj;
	TArray<TSharedPtr<FFireShotParticleCompChoice>> Choices;
	TArray<TSharedPtr<FFireShotEffectItem>> FireShotEffectEntries;
	TSharedPtr<IPropertyHandleArray> MyArrayProperty;
};

void FDBDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	TArray<TWeakObjectPtr<UObject>> Objects;
	DetailLayout.GetObjectsBeingCustomized(Objects);
	if (Objects.Num() == 1 && Objects[0].IsValid())
	{
		IDetailCategoryBuilder& WeaponCategory = DetailLayout.EditCategory("WeaponState");
		TSharedRef<IPropertyHandle> MuzzleFlash = DetailLayout.GetProperty(TEXT("m_FiringEffects"));

		uint32 NumChildren = 0;
		MuzzleFlash->GetNumChildren(NumChildren);
		TArray<TSharedPtr<FFireShotParticleCompChoice>> Choices;
		Choices.Add(MakeShareable(new FFireShotParticleCompChoice(NULL, NAME_None)));
		{
			TArray<USCS_Node*> ConstructionNodes;
			{
				TArray<const UBlueprintGeneratedClass*> ParentBPClassStack;
				UBlueprintGeneratedClass::GetGeneratedClassesHierarchy(Objects[0].Get()->GetClass(), ParentBPClassStack);
				for (int32 i = ParentBPClassStack.Num() - 1; i >= 0; i--)
				{
					const UBlueprintGeneratedClass* CurrentBPGClass = ParentBPClassStack[i];
					if (CurrentBPGClass->SimpleConstructionScript)
					{
						ConstructionNodes += CurrentBPGClass->SimpleConstructionScript->GetAllNodes();
					}
				}
			}
			TArray<UObject*> Children;
			for (UClass* TestClass = Objects[0].Get()->GetClass(); TestClass != NULL; TestClass = TestClass->GetSuperClass())
			{
				GetObjectsWithOuter(TestClass, Children, true, RF_NoFlags, EInternalObjectFlags::PendingKill);
			}
			for (int32 i = 0; i < Children.Num(); i++)
			{
				UParticleSystemComponent* PSC = Cast<UParticleSystemComponent>(Children[i]);
				if (PSC != NULL)
				{
					FName DisplayName = PSC->GetFName();
					for (int32 j = 0; j < ConstructionNodes.Num(); j++)
					{
						if (ConstructionNodes[j]->ComponentTemplate == PSC)
						{
							DisplayName = ConstructionNodes[j]->GetVariableName();
							break;
						}
					}
					Choices.Add(MakeShareable(new FFireShotParticleCompChoice(PSC, DisplayName)));
				}
			}
		}

		//WeaponCategory.AddCustomBuilder(MakeShareable(new FFireShotEffectArrayBuilder(Objects[0], MuzzleFlash, Choices, true)), false);
	}
}

#endif

