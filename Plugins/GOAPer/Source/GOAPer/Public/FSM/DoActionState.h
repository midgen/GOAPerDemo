#pragma once
#include "GOAPer.h"
#include "GOAPFSMState.h"
#include "GameFramework/Actor.h"
#include "GOAPAIController.h"

class DoActionState : public GOAPFSMState
{
public:

	DoActionState();
	~DoActionState();
	virtual TSharedPtr<GOAPFSMState> Tick(AGOAPAIController& controller, float DeltaTime) override;
	virtual void Enter(AGOAPAIController& controller) override;
	virtual FString ToString() override;
};

