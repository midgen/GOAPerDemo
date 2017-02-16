
#include "GOAPer.h"
#include "GOAPPlanner.h"
#include "GOAPNode.h"
#include "GOAPAtom.h"
#include "GOAPAction.h"
#include "GOAPAIController.h"



UGOAPPlanner::UGOAPPlanner(const FObjectInitializer &ObjectInitializer) :Super(ObjectInitializer)
{

}
/**
/*  Form a plan to satisfy the specified target state					
**/
TArray<TWeakObjectPtr<UGOAPAction>> UGOAPPlanner::Plan(UObject* aOuter, const uint8 aState, const bool aValue, TArray<UGOAPAction*>* aActions, FGOAPState* aCurrentState, AGOAPAIController& controller)
{
	
	OpenNodes.Empty();
	ClosedNodes.Empty(0);
	ClosedNodes.Reserve(500);
	GOAPPlan.Empty();

	// First build the graph, start building from current state
	FGOAPNode startNode;
	startNode.State = *aCurrentState;

	OpenNodes.Push(startNode);

	while (OpenNodes.Num() > 0)
	{
		ClosedNodes.Push(OpenNodes.Pop(false));

		FGOAPNode& workNode = ClosedNodes[ClosedNodes.Num() - 1];

		// Don't continue searching this branch if state is already satisfied
		if (!workNode.State.IsStateSatisfied(aState, aValue))
		{
			// Get all valid actions for this state to check
			for (auto& action : controller.GetValidActionsForState(workNode.State))
			{
				// Make sure we aren't caught in an action loop
				// e.g. EnterCover->ExitCover->EnterCover->ExitCover
				if (!workNode.Parent.Action.IsValid() || !workNode.Parent.Node->Parent.Action.IsValid() || action != workNode.Parent.Node->Parent.Action)
				{
					FGOAPNode newNode;
					newNode.State = workNode.State;
					newNode.State = newNode.State + action->Effects_Internal;
					newNode.Parent.Action = action;
					newNode.Parent.Node = &workNode;
					OpenNodes.Push(newNode);
				}
			}
		}

	}

	TArray<FGOAPNode*> ValidNodes;

	// Now find any nodes that meet the target state
	for (auto& node : ClosedNodes)
	{
		if (node.State.IsStateSatisfied(aState, aValue))
		{
			ValidNodes.Push(&node);
		}
	}

	// Now compile the list of plans
	TArray<TArray<TWeakObjectPtr<UGOAPAction>>> ValidPlans;

	for (auto& node : ValidNodes)
	{
		FGOAPNode* CurrentNode = node;
		TArray<TWeakObjectPtr<UGOAPAction>> CandidatePlan;
		while(CurrentNode->Parent.Action.IsValid())
		{
			CandidatePlan.Push(CurrentNode->Parent.Action);
			CurrentNode = CurrentNode->Parent.Node;
		}
		ValidPlans.Push(CandidatePlan);
	}

	// Now pick one, least number of actions will do for now
	int32 shortestPlan = INT_MAX;
	int16 index = 0;
	int16 shortPlanIndex = -1;
	for (auto& plan : ValidPlans)
	{
		if (plan.Num() < shortestPlan)
		{
			shortestPlan = plan.Num();
			shortPlanIndex = index;
		}
		++index;
	}
	if (shortPlanIndex > -1)
	{
		// Need to reverse the plan
		while (ValidPlans[shortPlanIndex].Num() > 0)
		{
			GOAPPlan.Push(ValidPlans[shortPlanIndex].Pop());
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Planning complete, nodes: " + FString::FromInt(ClosedNodes.Num()) + 
											", valid plans: " + FString::FromInt(ValidPlans.Num()) +
											", optimal length: " + FString::FromInt(GOAPPlan.Num())));

	return GOAPPlan;
}
