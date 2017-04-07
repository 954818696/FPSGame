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

	UPROPERTY(Instanced, EditDefaultsOnly, Category = WeaponState)
	class UDBWeaponStateActive* m_WeaponStateActive;

	UPROPERTY(Instanced, EditDefaultsOnly, Category = WeaponState)
	class UDBWeaponStateInactive* m_WeaponStateInactive;

	UPROPERTY(Instanced, EditDefaultsOnly, Category = WeaponState)
	TArray<class UDBWeaponStateFiring*> m_WeaponStateFiring;

	UPROPERTY(Instanced, EditDefaultsOnly, Category = WeaponState)
	class UDBWeaponStateEquipDirectly* m_WeaponStateEquipDirectly;

	UPROPERTY(Instanced, EditDefaultsOnly, Category = WeaponState)
	class UDBWeaponStateEquipFromInventory* m_WeaponStateEquipFromInventory;

	UPROPERTY(Instanced, EditDefaultsOnly, Category = WeaponState)
	class UDBWeaponStateUnEquiping* m_WeaponStateUnequiping;

	UPROPERTY(Instanced, EditDefaultsOnly, Category = WeaponState)
	class UDBWeaponStateSwitchMode* m_WeaponStateSwitchMode;

	UPROPERTY(Instanced, EditDefaultsOnly, Category = WeaponState)
	class UDBWeaponStateReload* m_WeaponStateReloading;

private:
	UDBWeaponStateBase* m_CurrentWeaponState;
	UDBWeaponStateBase* m_PrevWeaponState;

};
