// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "DBZombieAIController.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API ADBZombieAIController : public AAIController
{
	GENERATED_UCLASS_BODY()
	
public:
	virtual void Possess(class APawn* InPawn) override;

	virtual void UnPossess() override;

	class ADBBotWayPoint* GetWaypoint();

	class ADBBaseCharacter* GetTargetEnemy();

	void SetWaypoint(ADBBotWayPoint* NewWaypoint);

	void SetTargetEnemy(APawn* NewTarget);

	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return BehaviorComp; }

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }

	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName TargetEnemyKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName PatrolLocationKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName CurrentWaypointKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName BotTypeKeyName;
	
private:
	UBehaviorTreeComponent* BehaviorComp;

	UBlackboardComponent* BlackboardComp;
};
