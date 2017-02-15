// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GOAPer.h"
#include "AIController.h"
#include "GOAPerSettings.h"
#include "GOAPFSMState.h"
#include "GOAPAction.h"
#include "GOAPState.h"
#include "GOAPStateUI.h"
#include "GOAPPlanner.h"
#include "GOAPAtomKey.h"
#include "GameFramework/Actor.h"
#include "GOAPAIController.generated.h"

UCLASS()
class GOAPER_API AGOAPAIController : public AAIController
{
	GENERATED_BODY()
private:
	bool LoadGOAPDefaults();
	UPROPERTY()
	UGOAPPlanner* Planner;

protected:


public:

	// Flag to indicate we've set a new goal and are waiting for the idle state
	// To trigger a new plan. Set to true once we start a DoAction state
	bool IsIdlePendingPlan = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UGOAPerSettings* Settings = GetMutableDefault<UGOAPerSettings>();

	// Current FSM States
	TSharedPtr<GOAPFSMState> FSMstate;
	// The current active Plan
	TQueue<TWeakObjectPtr<UGOAPAction>>	ActionQueue;
	// Current active action
	TWeakObjectPtr<UGOAPAction>			CurrentAction;
	// Current goal
	FGOAPAtom CurrentGoal;
	// Current state
	FGOAPState GOAPState;
	// Available actions for this agent
	UPROPERTY()
	TArray<UGOAPAction*>	GOAPActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GOAPer | Agent Config")
	TArray<TSubclassOf<UGOAPAction>> AvailableActions;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GOAPer | Agent Config")
	FGOAPStateUI StartingState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GOAPer | Agent Config")
	FGOAPAtom DefaultGoal;
	



	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Switch FSM State
	void SetNewState(TSharedPtr<GOAPFSMState> newState);
	// Helper functions for switching state
	void SetDoActionState();
	void SetIdleState();
	// Helpers for changing to MoveToStates
	void SetMoveToStateWithTarget(TWeakObjectPtr<AActor> aTargetActor, float aAcceptanceRadius);
	// Move to a location, sets movetotarget to current character
	void SetMoveToStateWithLocation(FVector aLocation);

	// DWISOTT - Commonly used when perception stimulus causes us to need to replan
	void ClearCurrentActionAndPlan();
	// Activate the Planner for the current goal
	bool BuildActionPlanForCurrentGoal();

	TArray<UGOAPAction*> GetValidActionsForState(const FGOAPState aState);

	bool isStateSatisfied(FGOAPAtom aState);
	UFUNCTION(BlueprintCallable, Category = "GOAP")
	bool isStateSatisfied(FGOAPAtomKey Key, const bool Value);

	// Callback for MoveTo completion
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	// Helper functions for debug UI
	UFUNCTION(BlueprintCallable, Category = "GOAP")
	FString GetCurrentFSMStateString();
	UFUNCTION(BlueprintCallable, Category = "GOAP")
	FString GetCurrentActionString();

	UFUNCTION(BlueprintCallable, Category = "GOAP")
	void SetGOAPState(FGOAPAtomKey Key, bool Value);

	TWeakObjectPtr<AActor> MoveToTargetActor;

};