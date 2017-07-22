// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponStateMachine.h"
#include "DBWeaponStateActive.h"
#include "DBWeaponStateInactive.h"
#include "DBWeaponStateFiring.h"
#include "DBWeaponStateEquipFromInventory.h"
#include "DBWeaponStateEquipDirectly.h"
#include "DBWeaponStateUnEquiping.h"
#include "DBWeaponStateSwitchMode.h"
#include "DBWeaponStateReload.h"

UDBWeaponStateMachine::UDBWeaponStateMachine(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	m_CurrentWeaponState(nullptr),
	m_PrevWeaponState(nullptr)
{
	m_WeaponStateActive = ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateActive>(this, TEXT("WeaponStateActive"), false);
	m_WeaponStateInactive = ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateInactive>(this, TEXT("WeaponStateInactive"), false);
	m_WeaponStateEquipDirectly = ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateEquipDirectly>(this, TEXT("WeaponStateEquipDirectly"), false);
	m_WeaponStateEquipFromInventory = ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateEquipFromInventory>(this, TEXT("WeaponStateEquipFromInventory"), false);
	m_WeaponStateUnequiping = ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateUnEquiping>(this, TEXT("WeaponStateUnEquiping"), false);
	m_WeaponStateSwitchMode = ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateSwitchMode>(this, TEXT("WeaponStateSwitchMode"), false);
	m_WeaponStateReloading = ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateReload>(this, TEXT("WeaponStateReloading"), false);

	m_WeaponStateActive->SetOuterWeaponStateMachine(this);
	m_WeaponStateEquipDirectly->SetOuterWeaponStateMachine(this);
	m_WeaponStateEquipFromInventory->SetOuterWeaponStateMachine(this);
	m_WeaponStateUnequiping->SetOuterWeaponStateMachine(this);
	m_WeaponStateSwitchMode->SetOuterWeaponStateMachine(this);
	m_WeaponStateReloading->SetOuterWeaponStateMachine(this);
	m_WeaponStateInactive->SetOuterWeaponStateMachine(this);
}

void UDBWeaponStateMachine::InitStateMachine()
{
	m_WeaponStateEquipDirectly->InitState();
	m_WeaponStateEquipFromInventory->InitState();
}

UDBWeaponStateBase* UDBWeaponStateMachine::GetState(EWeaponState::Type WeaponState)
{
	UDBWeaponStateBase* TWeaponState = nullptr;
	switch (WeaponState)
	{
		case EWeaponState::EWeaponState_Active:
			TWeaponState = m_WeaponStateActive;
			break;
		case EWeaponState::EWeaponState_Inactive:
			TWeaponState = m_WeaponStateInactive;
			break;
		case EWeaponState::EWeaponState_Attack:
		{
			uint8 FireMode = GetOuterADBWeaponBase()->GetCurrentFireMode();
			TWeaponState = m_WeaponStateFiring[FireMode];
			break;
		}
		case EWeaponState:: EWeaponState_EquipingDirectly:
			TWeaponState = m_WeaponStateEquipDirectly;
			break;
		case EWeaponState::EWeaponState_EquipingFromInventory:
			TWeaponState = m_WeaponStateEquipFromInventory;
			break;
		case EWeaponState::EWeaponState_Unequiping:
			TWeaponState = m_WeaponStateUnequiping;
			break;
		case EWeaponState::EWeaponState_SwitchMode:
			TWeaponState = m_WeaponStateSwitchMode;
			break;
		case EWeaponState::EWeaponState_Reloading:
			TWeaponState = m_WeaponStateReloading;
			break;
		default:
		{
			DAWNBREAKERS_LOG_ERROR("UDBWeaponStateMachine::SetCurrentState Invalid State id = %d", (int32)WeaponState);
		}
	}

	return TWeaponState;
}

void UDBWeaponStateMachine::GotoState(EWeaponState::Type WeaponStateType)
{
	if (m_CurrentWeaponState && m_CurrentWeaponState->GetStateID() != WeaponStateType)
	{
		UDBWeaponStateBase* TWeaponState = GetState(WeaponStateType);
		if (TWeaponState)
		{
			if (m_CurrentWeaponState->CanTransferTo(WeaponStateType, TWeaponState))
			{
				m_PrevWeaponState = m_CurrentWeaponState;
				m_CurrentWeaponState->ExitWeaponState();
				m_CurrentWeaponState = TWeaponState;
				m_CurrentWeaponState->EnterWeaponState();
			}
		}
	}
}

void UDBWeaponStateMachine::SetStateDirectly(EWeaponState::Type WeaponStateType)
{
	m_CurrentWeaponState = GetState(WeaponStateType);
}

bool UDBWeaponStateMachine::IsInState(EWeaponState::Type WeaponState)
{
	if (m_CurrentWeaponState != nullptr && 
		m_CurrentWeaponState->IsValidLowLevel() &&
		m_CurrentWeaponState->GetStateID() == WeaponState)
	{
		return true;
	}

	return false;
}

class UDBWeaponStateBase* UDBWeaponStateMachine::GetPrevState() const
{
	return m_PrevWeaponState;
}

void UDBWeaponStateMachine::Tick(float DeltaTime)
{
	m_CurrentWeaponState->Tick(DeltaTime);
}


