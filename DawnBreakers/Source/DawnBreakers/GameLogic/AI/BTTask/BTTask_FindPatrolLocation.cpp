#include "DawnBreakers.h"
#include "BTTask_FindPatrolLocation.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "DawnBreakers/GameLogic/AI/Misc/DBBotWayPoint.h"
#include "DawnBreakers/GameLogic/AI/AIController/DBZombieAIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

EBTNodeResult::Type UBTTask_FindPatrolLocation::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	ADBZombieAIController* AIController = Cast<ADBZombieAIController>(OwnerComp.GetAIOwner());
	if (AIController == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	ADBBotWayPoint* MyWaypoint = AIController->GetWaypoint();
	if (MyWaypoint)
	{
		const float SearchRadius = 200.0f;
		const FVector SearchOrigin = AIController->ZombieWayPoint->GetActorLocation();
		FVector RandLoc;
		RandLoc = UNavigationSystem::GetRandomPointInNavigableRadius(AIController, SearchOrigin, SearchRadius);
		//if (FindResult)
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID(), RandLoc);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
