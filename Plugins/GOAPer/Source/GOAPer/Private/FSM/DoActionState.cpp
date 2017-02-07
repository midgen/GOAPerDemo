#include "GOAPer.h"
#include "DoActionState.h"
#include "IdleState.h"
#include "GOAPAction.h"
#include "GOAPAIController.h"

DoActionState::DoActionState()
{
	eState = EGOAPFSMState::DoAction;
}

DoActionState::~DoActionState()
{

}

TSharedPtr<GOAPFSMState> DoActionState::Tick(AGOAPAIController& controller, float DeltaTime)
{
	// Check if the preconditions are still valid, we need to invalidate the plan
	if (!controller.CurrentAction->ArePreconditionsSatisfied(&controller))
	{
		controller.CurrentAction = nullptr;
		controller.ActionQueue.Empty();
		return MakeShareable(new IdleState());
	}
	// Otherwise, crack on with it
	if (controller.CurrentAction->Execute(&controller))
	{
		// And clear the action
		controller.CurrentAction = nullptr;
		// Then return to idle
		return MakeShareable(new IdleState());
	}
	return nullptr;
}

void DoActionState::Enter(AGOAPAIController& controller)
{
	
}

FString DoActionState::ToString()
{
	return TEXT("DoAction");
}

