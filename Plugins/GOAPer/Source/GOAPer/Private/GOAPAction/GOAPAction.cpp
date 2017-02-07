#include "GOAPer.h"
#include "GOAPAIController.h"
#include "GameFramework/Actor.h"
#include "GOAPAction.h"

UGOAPAction::UGOAPAction(class FObjectInitializer const & ObjectInitializer) : Super(ObjectInitializer)
{}

bool UGOAPAction::ArePreconditionsSatisfied(AGOAPAIController* controller)
{
	if (PreConditions.State.Num() == 0)
	{
		return true;
	}

	return controller->GOAPState.IsSatisfiesState(PreConditions);
}

// Checks if the Agent is within the Interaction Range of the TargetActor
bool UGOAPAction::IsInRange(AGOAPAIController* controller)
{
	// Otherwise, check the distance against the interaction range
	return ((ActionTarget !=  nullptr) && (controller->GetPawn()->GetActorLocation() - ActionTarget->GetActorLocation()).Size() < InteractionRange);
}

bool UGOAPAction::AreEffectsSatisfied(AGOAPAIController* controller)
{
	 return controller->GOAPState.IsSatisfiesState(Effects);
}