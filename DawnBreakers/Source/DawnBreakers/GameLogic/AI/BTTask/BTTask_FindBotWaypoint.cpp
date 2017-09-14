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

	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID(), AIController->ZombieWayPoint);
	return EBTNodeResult::Succeeded;
}
