#pragma once
#include "GOAPer.h"
#include "GOAPFSMState.h"
#include "GOAPAIController.h"

class IdleState : public GOAPFSMState
{
public:

	IdleState();
	~IdleState();
	virtual TSharedPtr<GOAPFSMState> Tick(AGOAPAIController& controller, float DeltaTime) override;
	virtual void Enter(AGOAPAIController& controller) override;
	virtual FString ToString() override;
private:
		float timeWaited;
		const float TIME_TO_WAIT = 0.1f;

};

