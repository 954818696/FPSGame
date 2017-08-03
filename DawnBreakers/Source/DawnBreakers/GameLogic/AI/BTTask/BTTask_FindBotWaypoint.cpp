#include "DawnBreakers.h"
#include "BTTask_FindBotWaypoint.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "DawnBreakers/GameLogic/AI/Misc/DBBotWayPoint.h"
#include "DawnBreakers/GameLogic/AI/AIController/DBZombieAIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"


EBTNodeResult::Type UBTTask_FindBotWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ADBZombieAIController* AIController = Cast<ADBZombieAIController>(OwnerComp.GetAIOwner());
	if (AIController == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	ADBBotWayPoint* CurrentWaypoint = AIController->GetWaypoint();
	AActor* NewWaypoint = nullptr;

	TArray<AActor*> AllWaypoints;
	UGameplayStatics::GetAllActorsOfClass(AIController, ADBBotWayPoint::StaticClass(), AllWaypoints);

	if (AllWaypoints.Num() == 0)
	{
		return EBTNodeResult::Failed;
	}
		
	NewWaypoint = AllWaypoints[FMath::RandRange(0, AllWaypoints.Num() - 1)];

	if (NewWaypoint)
	{
		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID(), NewWaypoint);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
