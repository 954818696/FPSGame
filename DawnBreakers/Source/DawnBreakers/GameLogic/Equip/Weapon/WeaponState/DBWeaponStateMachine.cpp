// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBWeaponStateMachine.h"
#include "DBWeaponStateActive.h"
#include "DBWeaponStateInactive.h"
#include "DBWeaponStateFiring.h"
#include "DBWeaponStateEquiping.h"
#include "DBWeaponStateUnEquiping.h"
#include "DBWeaponStateSwitchMode.h"
#include "DBWeaponStateReload.h"

UDBWeaponStateMachine::UDBWeaponStateMachine(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_WeaponStateActive			= ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateActive>(this, TEXT("WeaponStateActive"), false);
	m_WeaponStateInactive		= ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateInactive>(this, TEXT("WeaponStateInactive"), false);
	m_WeaponStateEquiping		= ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateEquiping>(this, TEXT("WeaponStateEquiping"), false);
	m_WeaponStateUnequiping	= ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateUnEquiping>(this, TEXT("WeaponStateUnEquiping"), false);
	m_WeaponStateSwitchMode	= ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateSwitchMode>(this, TEXT("WeaponStateSwitchMode"), false);
	m_WeaponStateReloading		= ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateReload>(this, TEXT("WeaponStateReloading"), false);

	// Multi-Fire Mode.
	//for (int32 i = 0; i < m_TotalFireModes; ++i)
	//{
	//	FName ObjName = *FString::Printf(TEXT("WeaponStateFiring%d"), i);
	//	m_WeaponStateFiring.Add(ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateFiring>(this, ObjName, false));
	//}
	m_WeaponStateFiring.Add(ObjectInitializer.CreateDefaultSubobject<UDBWeaponStateFiring>(this, TEXT("WeaponStateFiring"), false));
}

void UDBWeaponStateMachine::SetCurrentState(EWeaponState::Type WeaponState)
{
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

		break;
	case EWeaponState::EWeaponState_Equiping:
		m_CurrentWeaponState = m_WeaponStateEquiping;
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
		DAWNBREAKERS_LOG_ERROR("UDBWeaponStateMachine::SetCurrentState Invalid State id = %d", (int32)WeaponState);
	}
}

void UDBWeaponStateMachine::GotoState(EWeaponState::Type WeaponState)
{

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


