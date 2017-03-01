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
	: Super(ObjectInitializer)
{
	m_WeaponStateActive = ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateActive>(this, TEXT("WeaponStateActive"), false);
	m_WeaponStateInactive = ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateInactive>(this, TEXT("WeaponStateInactive"), false);
	m_WeaponStateEquipDirectly = ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateEquipDirectly>(this, TEXT("WeaponStateEquipDirectly"), false);
	m_WeaponStateEquipFromInventory = ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateEquipFromInventory>(this, TEXT("WeaponStateEquipFromInventory"), false);
	m_WeaponStateUnequiping = ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateUnEquiping>(this, TEXT("WeaponStateUnEquiping"), false);
	m_WeaponStateSwitchMode = ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateSwitchMode>(this, TEXT("WeaponStateSwitchMode"), false);
	m_WeaponStateReloading = ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateReload>(this, TEXT("WeaponStateReloading"), false);
	// Multi-Fire Mode.
	//for (int32 i = 0; i < m_TotalFireModes; ++i)
	//{
	//	FName ObjName = *FString::Printf(TEXT("WeaponStateFiring%d"), i);
	//	m_WeaponStateFiring.Add(ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateFiring>(this, ObjName, false));
	//}
	m_WeaponStateFiring.Add(ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateFiring>(this, TEXT("WeaponStateFiring"), false));

	m_CurrentWeaponState = m_WeaponStateInactive;
}

void UDBWeaponStateMachine::InitStateMachine()
{
	m_WeaponStateEquipDirectly->InitState();
	m_WeaponStateEquipFromInventory->InitState();
}

bool UDBWeaponStateMachine::SetCurrentState(EWeaponState::Type WeaponState)
{
	bool bResult = true;
	switch (WeaponState)
	{
		case EWeaponState::EWeaponState_Active:
			m_CurrentWeaponState = m_WeaponStateActive;
			break;
		case EWeaponState::EWeaponState_Inactive:
			m_CurrentWeaponState = m_WeaponStateInactive;
			break;
		case EWeaponState::EWeaponState_Firing:
		{
			uint8 FireMode = GetOuterADBWeaponBase()->GetCurrentFireMode();
			m_CurrentWeaponState = m_WeaponStateFiring[FireMode];
		}
		case EWeaponState:: EWeaponState_EquipingDirectly:
			m_CurrentWeaponState = m_WeaponStateEquipDirectly;
			break;
		case EWeaponState::EWeaponState_EquipingFromInventory:
			m_CurrentWeaponState = m_WeaponStateEquipFromInventory;
			break;
		case EWeaponState::EWeaponState_Unequiping:
			m_CurrentWeaponState = m_WeaponStateUnequiping;
			break;
		case EWeaponState::EWeaponState_SwitchMode:
			m_CurrentWeaponState = m_WeaponStateSwitchMode;
			break;
		case EWeaponState::EWeaponState_Reloading:
			m_CurrentWeaponState = m_WeaponStateReloading;
			break;
		default:
		{
			bResult = false;
			DAWNBREAKERS_LOG_ERROR("UDBWeaponStateMachine::SetCurrentState Invalid State id = %d", (int32)WeaponState);
		}
	}

	return bResult;
}

void UDBWeaponStateMachine::GotoState(EWeaponState::Type WeaponState)
{
	if (m_CurrentWeaponState && m_CurrentWeaponState->GetStateID() != WeaponState)
	{
		if (m_CurrentWeaponState->CanTransferTo(WeaponState))
		{
			m_CurrentWeaponState->ExitWeaponState();
			bool bSuccess = SetCurrentState(WeaponState);
			if (bSuccess)
			{
				m_CurrentWeaponState->EnterWeaponState();
			}
		}
	}
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

void UDBWeaponStateMachine::Tick(float DeltaTime)
{
	m_CurrentWeaponState->Tick(DeltaTime);
}


