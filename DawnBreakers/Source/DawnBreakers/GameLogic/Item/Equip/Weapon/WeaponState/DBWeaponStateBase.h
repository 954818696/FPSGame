// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "DBWeaponStateBase.generated.h"

namespace EWeaponState
{
	enum Type
	{
		EWeaponState_Invalid = -1,
		EWeaponState_Active = 0,												// �Ѿ�װ��������
		EWeaponState_Inactive = 1,												// ���ڱ�����
		EWeaponState_Firing = 2,												// ����
		EWeaponState_EquipingDirectly = 3,								// ֱ�Ӽ�����װ��
		EWeaponState_EquipingFromInventory = 4,					// �ѱ������ȡ��װ��������
		EWeaponState_Unequiping = 5,										// �������Ƶ�����
		EWeaponState_SwitchMode = 6,										// �л�����ģʽ
		EWeaponState_Reloading = 7,											// װ���ӵ�

		EWeaponState_Max = 8,
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

	virtual void EnterWeaponState() {}

	virtual void ExitWeaponState() {}

	virtual bool IsHandled() { return false; }

	virtual void Tick(float DeltaTime) {}

	FORCEINLINE EWeaponState::Type GetStateID() const { return m_StateID; }

protected:
	EWeaponState::Type m_StateID;
	
};
