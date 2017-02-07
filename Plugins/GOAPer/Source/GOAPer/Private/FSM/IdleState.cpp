#include "GOAPer.h"
#include "IdleState.h"
#include "MoveToState.h"
#include "DoActionState.h"
#include "GOAPAction.h"
#include "GOAPAIController.h"

IdleState::IdleState()
{
	eState = EGOAPFSMState::Idle;
}

IdleState::~IdleState()
{

}

TSharedPtr<GOAPFSMState> IdleState::Tick(AGOAPAIController& controller, float DeltaTime)
{
	timeWaited += DeltaTime;
	if (timeWaited > TIME_TO_WAIT)
	{
		timeWaited = 0.0f;
		// If we don't have a current action waiting....
		if((&controller)->CurrentAction == nullptr)
		{
			// If there's nothing queued, we need to try and form a plan
			if ((&controller)->ActionQueue.IsEmpty())
			{
				// If we can form a plan
				if ((&controller)->BuildActionPlanForCurrentGoal())
				{
					// If the goal is already satisfied, trash the queue, we'll try another one next idle tick
					if ((&controller)->isStateSatisfied(controller.CurrentGoal))
					{
						(&controller)->ActionQueue.Empty();
						return nullptr;
					}

				
					(&controller)->ActionQueue.Dequeue((&controller)->CurrentAction);
					return MakeShareable(new DoActionState());
				}
			}
			else
			{
				(&controller)->ActionQueue.Dequeue((&controller)->CurrentAction);
				return MakeShareable(new DoActionState());
			}
		}
		// Otherwise, we have a current action, so switch to DoAction and get on with it
		else
		{	
			return MakeShareable(new DoActionState());
		}
	}
	
	// Otherwise, just stay idle
	return nullptr;
}

void IdleState::Enter(AGOAPAIController& controller)
{
	timeWaited = 0.0f;
}

FString IdleState::ToString()
{
	return TEXT("Idle");
}

