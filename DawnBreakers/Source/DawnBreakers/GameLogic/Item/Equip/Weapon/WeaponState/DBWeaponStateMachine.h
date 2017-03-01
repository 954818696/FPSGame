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

	bool SetCurrentState(EWeaponState::Type WeaponState);

	void GotoState(EWeaponState::Type WeaponState);

	bool IsInState(EWeaponState::Type WeaponState);

	void Tick(float DeltaTime);
	
protected:

	UPROPERTY(Instanced, EditDefaultsOnly, NoClear, Category = WeaponState)
	class UDBWeaponStateActive* m_WeaponStateActive;

	UPROPERTY(Instanced, EditDefaultsOnly, NoClear, Category = WeaponState)
	class UDBWeaponStateInactive* m_WeaponStateInactive;

	UPROPERTY(Instanced, EditDefaultsOnly, NoClear, Category = WeaponState)
	TArray<class UDBWeaponStateFiring*> m_WeaponStateFiring;

	UPROPERTY(Instanced, EditDefaultsOnly, NoClear, Category = WeaponState)
	class UDBWeaponStateEquipDirectly* m_WeaponStateEquipDirectly;

	UPROPERTY(Instanced, EditDefaultsOnly, NoClear, Category = WeaponState)
	class UDBWeaponStateEquipFromInventory* m_WeaponStateEquipFromInventory;

	UPROPERTY(Instanced, EditDefaultsOnly, NoClear, Category = WeaponState)
	class UDBWeaponStateUnEquiping* m_WeaponStateUnequiping;

	UPROPERTY(Instanced, EditDefaultsOnly, NoClear, Category = WeaponState)
	class UDBWeaponStateSwitchMode* m_WeaponStateSwitchMode;

	UPROPERTY(Instanced, EditDefaultsOnly, NoClear, Category = WeaponState)
	class UDBWeaponStateReload* m_WeaponStateReloading;

private:
	class UDBWeaponStateBase* m_CurrentWeaponState;

};
