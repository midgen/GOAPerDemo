
#include "GOAPer.h"
#include "MoveToState.h"

MoveToState::MoveToState()
{
	eState = EGOAPFSMState::MoveTo;
}

MoveToState::~MoveToState()
{

}

TSharedPtr<GOAPFSMState> MoveToState::Tick(AGOAPAIController& controller, float DeltaTime)
{
	// Stop the movement action if the target isn't valid any more
	if (!controller.MoveToTargetActor.IsValid(false))
	{
		controller.StopMovement();
		return MakeShareable(new IdleState());
	}
	TSharedPtr<GOAPFSMState> retVal;
	return retVal;
}

void MoveToState::Enter(AGOAPAIController& controller)
{

}

FString MoveToState::ToString()
{
	return TEXT("MoveTo");
}

