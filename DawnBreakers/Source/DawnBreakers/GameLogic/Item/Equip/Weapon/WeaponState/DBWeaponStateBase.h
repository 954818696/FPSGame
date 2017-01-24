// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "DBWeaponStateBase.generated.h"

namespace EWeaponState
{
	enum Type
	{
		EWeaponState_Invalid = -1,
		EWeaponState_Active = 0,
		EWeaponState_Inactive = 1,
		EWeaponState_Firing = 2,
		EWeaponState_Equiping = 3,
		EWeaponState_Unequiping = 4,
		EWeaponState_SwitchMode = 5,
		EWeaponState_Reloading = 6,

		EWeaponState_Max = 7,
	};
}

/**
 * 
 */
UCLASS(DefaultToInstanced, EditInlineNew, Within = DBWeaponStateMachine)
class DAWNBREAKERS_API UDBWeaponStateBase : public UObject
{
	GENERATED_BODY()

public:

	virtual void EnterWeaponState(const UDBWeaponStateBase* PrevWeaponState) {}

	virtual void ExitWeaponState() {}

	virtual bool IsHandled() { return false; }

	virtual void Tick(float DeltaTime) {}

	FORCEINLINE EWeaponState::Type GetStateID() const { return m_StateID; }

protected:
	EWeaponState::Type m_StateID;
	
};
