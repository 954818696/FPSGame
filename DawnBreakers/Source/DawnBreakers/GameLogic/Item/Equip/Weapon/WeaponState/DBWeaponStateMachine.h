// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "DBWeaponStateBase.h"
#include "DBWeaponStateMachine.generated.h"



/**
 * 
 */
UCLASS(DefaultToInstanced, Within = DBWeaponBase)
class DAWNBREAKERS_API UDBWeaponStateMachine : public UObject
{
	GENERATED_UCLASS_BODY()
	
public:
	void InitStateMachine();

	UDBWeaponStateBase* GetState(EWeaponState::Type WeaponStateType);

	void GotoState(EWeaponState::Type WeaponStateType);

	void SetStateDirectly(EWeaponState::Type WeaponStateType);

	bool IsInState(EWeaponState::Type WeaponStateType);

	FORCEINLINE class UDBWeaponStateBase* GetPrevState() const;

	void Tick(float DeltaTime);
	
public:

	UPROPERTY()
	class UDBWeaponStateActive* m_WeaponStateActive;

	UPROPERTY()
	class UDBWeaponStateInactive* m_WeaponStateInactive;

	UPROPERTY()
	TArray<class UDBWeaponStateFiring*> m_WeaponStateFiring;

	UPROPERTY()
	class UDBWeaponStateEquipDirectly* m_WeaponStateEquipDirectly;

	UPROPERTY()
	class UDBWeaponStateEquipFromInventory* m_WeaponStateEquipFromInventory;

	UPROPERTY()
	class UDBWeaponStateUnEquiping* m_WeaponStateUnequiping;

	UPROPERTY()
	class UDBWeaponStateSwitchMode* m_WeaponStateSwitchMode;

	UPROPERTY()
	class UDBWeaponStateReload* m_WeaponStateReloading;

	UPROPERTY()
	class UDBWeaponStateDrop* m_WeaponStateDrop;

private:
	UDBWeaponStateBase* m_CurrentWeaponState;
	UDBWeaponStateBase* m_PrevWeaponState;

};
