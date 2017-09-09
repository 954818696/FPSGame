// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponBase.h"

#include "DawnBreakers/GameLogic/Item/Equip/Weapon/WeaponState/DBWeaponStateActive.h"
#include "DawnBreakers/GameLogic/Item/Equip/Weapon/WeaponState/DBWeaponStateEquipDirectly.h"
#include "DawnBreakers/GameLogic/Item/Equip/Weapon/WeaponState/DBWeaponStateEquipFromInventory.h"
#include "DawnBreakers/GameLogic/Item/Equip/Weapon/WeaponState/DBWeaponStateFiring.h"
#include "DawnBreakers/GameLogic/Item/Equip/Weapon/WeaponState/DBWeaponStateInactive.h"

ADBWeaponBase::ADBWeaponBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	m_CurrentFireMode(0)
{
	m_WeaponStateMachine = ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateMachine>(this, TEXT("WeaponStateMachine"), false);
}

void ADBWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	SetInstanceOnFireEffectArray(this, FireShotEffect);

	for (int32 i = 0; i < FireShotEffect.Num(); i++)
	{
		if (FireShotEffect[i] != NULL)
		{
			if (RootComponent == NULL && FireShotEffect[i]->IsRegistered())
			{
				FireShotEffect[i]->DeactivateSystem();
				FireShotEffect[i]->KillParticlesForced();
				FireShotEffect[i]->UnregisterComponent();
				FireShotEffect[i]->bWasActive = false;
			}
			FireShotEffect[i]->bAutoActivate = false;
			FireShotEffect[i]->SecondsBeforeInactive = 0.0f;
			FireShotEffect[i]->SetOnlyOwnerSee(false);
			FireShotEffect[i]->bUseAttachParentBound = true;
		}
	}


	MapStateToStateMachine();
}

void ADBWeaponBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();


}

void ADBWeaponBase::OnEquip(bool bEquipedWeaponFromInventory)
{
	if (bEquipedWeaponFromInventory)
	{
		m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_EquipingFromInventory);
	}
	else 
	{
		m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_EquipingDirectly);
	}
}

void ADBWeaponBase::OnUnEquip()
{
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_Unequiping);
}

void ADBWeaponBase::OnDrop()
{
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_Drop);
}

void ADBWeaponBase::OnStartFire()
{
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_Attack);
}

void ADBWeaponBase::OnStopFire()
{
	m_WeaponStateMachine->GotoState(EWeaponState::EWeaponState_Active);
}

UAudioComponent* ADBWeaponBase::PlayWeaponSound(USoundBase* Sound)
{
	UAudioComponent* TAuidioComp = nullptr;
	if (Sound)
	{
		TAuidioComp = UGameplayStatics::SpawnSoundAttached(Sound, GetItemOwner()->GetRootComponent());
	}

	return TAuidioComp;
}

bool ADBWeaponBase::IsInState(EWeaponState::Type WeaponState) const
{
	if (m_WeaponStateMachine->IsInState(WeaponState))
	{
		return true;
	}

	return false;
}

int32 ADBWeaponBase::GetWeaponHoldStanceType()
{
	return (int32)m_WeaponHoldType;
}

FORCEINLINE void ADBWeaponBase::PlayFireShotEffectByIndex(int32 EffectIndex)
{
	if (EffectIndex < 0)
	{
		return;
	}
	FireShotEffect[EffectIndex]->ActivateSystem();
}

FORCEINLINE void ADBWeaponBase::StopFireShotEffectByIndex(int32 EffectIndex)
{
	if (EffectIndex == -1)
		return;
	FireShotEffect[EffectIndex]->DeactivateSystem();
}

void ADBWeaponBase::SetInstanceOnFireEffectArray(AActor* Weapon, TArray<UParticleSystemComponent*>& OnFireEffectArray)
{
	TArray<const UBlueprintGeneratedClass*> ParentBPClassStack;
	UBlueprintGeneratedClass::GetGeneratedClassesHierarchy(Weapon->GetClass(), ParentBPClassStack);
	for (int32 i = ParentBPClassStack.Num() - 1; i >= 0; i--)
	{
		const UBlueprintGeneratedClass* CurrentBPGClass = ParentBPClassStack[i];
		if (CurrentBPGClass->SimpleConstructionScript)
		{
			TArray<USCS_Node*> ConstructionNodes = CurrentBPGClass->SimpleConstructionScript->GetAllNodes();
			for (int32 j = 0; j < ConstructionNodes.Num(); j++)
			{
				for (int32 k = 0; k < OnFireEffectArray.Num(); k++)
				{
					if (Cast<UParticleSystemComponent>(ConstructionNodes[j]->ComponentTemplate) == OnFireEffectArray[k])
					{
						OnFireEffectArray[k] = Cast<UParticleSystemComponent>((UObject*)FindObjectWithOuter(Weapon, ConstructionNodes[j]->ComponentTemplate->GetClass(), ConstructionNodes[j]->GetVariableName()));
					}
				}
			}
		}
	}
}

void ADBWeaponBase::MapStateToStateMachine()
{
	// For old support.....ue4 bug.
	m_WeaponStateMachine->m_WeaponStateFiring.Empty();


	for (int32 i = 0; i < m_WeaponStates.Num(); ++i)
	{
		m_WeaponStates[i]->SetOuterWeaponStateMachine(m_WeaponStateMachine);

		switch (m_WeaponStates[i]->GetStateID())
		{
		case EWeaponState::EWeaponState_Active:
			m_WeaponStateMachine->m_WeaponStateActive =  Cast<UDBWeaponStateActive>(m_WeaponStates[i]);
			break;
		case EWeaponState::EWeaponState_Inactive:
			m_WeaponStateMachine->m_WeaponStateInactive = Cast<UDBWeaponStateInactive>(m_WeaponStates[i]);
			break;
		case EWeaponState::EWeaponState_Attack:
		{
			UDBWeaponStateFiring* AttackState = Cast<UDBWeaponStateFiring>(m_WeaponStates[i]);
			if (AttackState)
			{
				m_WeaponStateMachine->m_WeaponStateFiring.Add(AttackState);
			}
			break;
		}
		case EWeaponState::EWeaponState_EquipingDirectly:
			m_WeaponStateMachine->m_WeaponStateEquipDirectly = Cast<UDBWeaponStateEquipDirectly>(m_WeaponStates[i]);
			break;
		case EWeaponState::EWeaponState_EquipingFromInventory:
			m_WeaponStateMachine->m_WeaponStateEquipFromInventory = Cast<UDBWeaponStateEquipFromInventory>(m_WeaponStates[i]);
			break;
		case EWeaponState::EWeaponState_Unequiping:
			m_WeaponStateMachine->m_WeaponStateUnequiping = Cast<UDBWeaponStateUnEquiping>(m_WeaponStates[i]);
			break;
		case EWeaponState::EWeaponState_SwitchMode:
			m_WeaponStateMachine->m_WeaponStateSwitchMode = Cast<UDBWeaponStateSwitchMode>(m_WeaponStates[i]);
			break;
		case EWeaponState::EWeaponState_Reloading:
			m_WeaponStateMachine->m_WeaponStateReloading = Cast<UDBWeaponStateReload>(m_WeaponStates[i]);
			break;
		default:
			DAWNBREAKERS_LOG_WARNING("InitWeapStateMachine invalid stateID:%d", (int32)m_WeaponStates[i]->GetStateID());
		}
	}

	m_WeaponStateMachine->SetStateDirectly(EWeaponState::EWeaponState_Inactive);
}
